#include "xTimeuil.h"
#include <iostream>
#include "xStringuil.h"
namespace SEABASE
{

    static struct tm* localtime_r(const time_t* timep, struct tm* result = NULL) {
#ifdef WIN32
        (void)result;
        return localtime(timep);
#else
        return ::localtime_r(timep, result);
#endif
    }

#ifdef _WIN32
    //gettimeofday ������http://suacommunity.com/dictionary/gettimeofday-entry.php
    FILETIME xTimeUtil::_ft = {0};
	LARGE_INTEGER xTimeUtil::_pform = {0};
#endif
	  
    int32_t xTimeUtil::gettimeofday(struct ::timeval *tv, struct timezone *tz)
    {
#ifndef _WIN32
        return ::gettimeofday(tv,tz);
#else
        FILETIME ft;

        unsigned __int64 tmpres = 0;
        unsigned __int64 tmpres2 = 0;
        static int tzflag = 0;
        LARGE_INTEGER pform={0};
        QueryPerformanceCounter(&pform);

        if (NULL != tv)
        {
            GetSystemTimeAsFileTime(&ft);
            if(ft.dwLowDateTime == _ft.dwLowDateTime && ft.dwHighDateTime == _ft.dwHighDateTime)
            {
                //ʱ�����ʱ������ʱ��ƫ��
                LARGE_INTEGER pfreq = {0};
                QueryPerformanceFrequency(&pfreq);
                tmpres2 = ((pform.QuadPart - _pform.QuadPart) * 1000000UL)/pfreq.QuadPart;
            }
            else
            {
                //ʱ�䲻��ʱ�����±�׼ʱ��
                xTimeUtil::_ft = ft;
                QueryPerformanceCounter(&_pform);
            }

            tmpres |= ft.dwHighDateTime;
            tmpres <<= 32;
            tmpres |= ft.dwLowDateTime;

            tmpres /= 10;
            tmpres -= DELTA_EPOCH_IN_MICROSECS;
			tmpres += tmpres2;	//��������ƫ��


            tv->tv_sec = (long)(tmpres / 1000000UL);
            tv->tv_usec = (long)(tmpres % 1000000UL);
        }

        if (NULL != tz)
        {
            if (!tzflag)
            {
                _tzset();
                tzflag++;
            }

            tz->tz_minuteswest = _timezone / 60;
            tz->tz_dsttime = _daylight;
        }

        return 0;
#endif
    }

    uint64_t xTimeUtil::get_timestamp_s() {
        struct ::timeval tv = {0, 0};
		gettimeofday(&tv, NULL);
        return tv.tv_sec;
    }

    uint64_t xTimeUtil::get_timestamp_ms() {
        struct ::timeval tv = {0, 0};
        gettimeofday(&tv, NULL);
        return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }

    uint64_t xTimeUtil::get_timestamp_us() {
        struct ::timeval tv = {0, 0};
        gettimeofday(&tv, NULL);
        return (uint64_t)tv.tv_sec * 1000000 + tv.tv_usec;
    }

    void xTimeUtil::safe_sleep_s(uint32_t second) {
#ifdef _WIN32
        return xTimeUtil::safe_sleep_ms(second * 1000);
#else
        struct timespec interval, remainder;
        int32_t ret;

        interval.tv_sec = second;
        interval.tv_nsec = 0;

        ret = nanosleep(&interval, &remainder);
        if (-1 == ret) {
            while (EINTR == errno && -1 == ret) {
                ret = nanosleep(&remainder, &remainder);
            }
        }
#endif
    }

    void xTimeUtil::safe_sleep_ms(uint32_t millisecond) {
#ifdef _WIN32
        ::Sleep(millisecond);
#else
        struct timespec interval, remainder;
        int32_t ret;

        interval.tv_sec = millisecond / 1000U;
        interval.tv_nsec = (uint64_t)millisecond % 1000UL * 1000UL * 1000UL;

        ret = nanosleep(&interval, &remainder);
        if (-1 == ret) {
            while (EINTR == errno && -1 == ret) {
                ret = nanosleep(&remainder, &remainder);
            }
        }
#endif
    }

    std::string xTimeUtil::format_datetime_str(uint64_t millisecond) {
        time_t time = (time_t)(millisecond / 1000);
        struct tm t;
        struct tm *pt = NULL;
        char buffer[24] = {0};

        pt = SEABASE::localtime_r(&time, &t);
        if(NULL != pt)
        {
            t = *pt;
            snprintf(buffer, 24, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int32_t)(millisecond % 1000));
        }
        return std::string(buffer);
    }

#ifndef _WIN32
    int32_t xTimeUtil::get_abs_timespec(struct timespec* ts, int32_t millisecond) {
        struct timeval tv;
        int32_t ret;

        if (NULL == ts) {
            return EINVAL;
        }

        ret = gettimeofday(&tv, NULL);
        if (0 != ret) {
            return ret;
        }

        ts->tv_sec = tv.tv_sec;
        ts->tv_nsec = tv.tv_usec * 1000UL;

        ts->tv_sec += millisecond / 1000UL;
        ts->tv_nsec += millisecond % 1000UL * 1000000UL;

        ts->tv_sec += ts->tv_nsec/(1000UL * 1000UL *1000UL);
        ts->tv_nsec %= (1000UL * 1000UL *1000UL);

        return 0;
    }
#endif

    int32_t xTimeUtil::strftimeval(char* buffer, int32_t buflen, const struct timeval* tv) {
        if (NULL == buffer || NULL == tv) {
            return -1;
        }

        time_t time = tv->tv_sec;
        struct tm t;
        struct tm *pt = NULL;

        pt = SEABASE::localtime_r(&time, &t);
        if(NULL == pt)
        {
            return -1;
        }
        t = *pt;
        return snprintf(buffer, buflen, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
                t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, (int32_t)tv->tv_usec / 1000);   
    }

    std::string xTimeUtil::get_date() {
        time_t t = time(NULL);
        struct tm result;
        struct tm *presult = NULL;
        char buffer[20] = {0};
        presult = SEABASE::localtime_r(&t, &result);
        if(NULL != presult)
        {
            result = *presult;
            strftime(buffer, 20, "%Y%m%d", &result);
        }

        return std::string(buffer);
    }

    std::string xTimeUtil::get_time() {
        time_t t = time(NULL);
        struct tm result;
        struct tm *presult = NULL;
        char buffer[20] = {0};
        presult = SEABASE::localtime_r(&t, &result);
        if(NULL != presult)
        {
            result = *presult;
            strftime(buffer, 20, "%H%M%S", &result);
        }

        return std::string(buffer);
    }
	//��ȡ��ǰʱ������ַ�����ʽ
	//��ʽ��YYYY-MM-DD HH:MI:SS.ms
	string xTimeUtil::getCurrentTimeStamp()
	{
		struct timeval tv;
		struct timezone tz;
		gettimeofday(&tv , &tz);

		time_t now = time(0);
		struct tm *ts = localtime(&now);
		if (!ts)
			return "";
		char buf[24] = {'\0'};
		//sprintf ���ܻᷢ��Խ�磬�����Զ����'\0',ʹ��snprintf
		snprintf(buf,23,"%04d-%02d-%02d %02d:%02d:%02d.%03d",
			ts->tm_year + 1900, ts->tm_mon+1,ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec,tv.tv_usec);
		printf("time=%s\n",buf);
		return buf;
	}
    int32_t xTimeUtil::get_day()
    {
        time_t t = time(NULL);
        struct tm result;
        struct tm *presult = NULL;
        presult = SEABASE::localtime_r(&t, &result);
        if(NULL == presult)
        {
            return -1;
        }
        result = *presult;
        return result.tm_wday;
    }

    int32_t xTimeUtil::get_day( time_t time )
    {
        struct tm result;
        struct tm *presult = NULL;
        presult = SEABASE::localtime_r(&time, &result);
        if(NULL == presult)
        {
            return -1;
        }
        result = *presult;
        return result.tm_wday;
    }

    std::string xTimeUtil::format_time(const char * fmt)
    {
        //��ȡʱ��
        struct ::timeval tv = {0, 0};
        gettimeofday(&tv, NULL);
        
        return format_time(&tv, fmt);
    }
    
    std::string xTimeUtil::format_time(time_t time, const char * fmt)
    {
        struct ::timeval tv = {0, 0};
        tv.tv_sec = static_cast <long>(time);

        return format_time(&tv, fmt);
    }

    std::string xTimeUtil::format_time(const struct timeval* tv, const char * fmt)
    {
        struct tm result;
        struct tm  *presult = NULL;
        time_t t = tv->tv_sec;
        char buffer[50] = {0};
        char tmp[8];
        if(NULL == fmt)
        {
            //��ʽ����ǰʱ��
            presult = SEABASE::localtime_r(&t, &result);
            if(NULL != presult)
            {
                result = *presult;
                strftime(buffer, sizeof(buffer), "%Y%m%d-%H:%M:%S", &result);
            }
        }
        else
        {
            std::string str_fmt(fmt);
            std::string str_tmp;
            if(std::string::npos != str_fmt.find("[m]"))
            {
                //�滻����ʱ��
                snprintf(tmp,8,"%03d", (int)(tv->tv_usec / 1000) );
                str_tmp.assign(tmp);
                str_fmt = xStringUtil::replace_string(str_fmt, "[m]", str_tmp);
            }
            if(std::string::npos != str_fmt.find("[u]"))
            {
                //�滻΢��ʱ��
                snprintf(tmp,8,"%06d", (int)(tv->tv_usec) );
                str_tmp.assign(tmp);
                str_fmt = xStringUtil::replace_string(str_fmt, "[u]", str_tmp);
            }
            if(std::string::npos != str_fmt.find("[U]"))
            {
                //�滻΢��ʱ��
                snprintf(tmp,8,"%03d", (int)(tv->tv_usec % 1000) );
                str_tmp.assign(tmp);
                str_fmt = xStringUtil::replace_string(str_fmt, "[U]", str_tmp);
            }
            presult = SEABASE::localtime_r(&t, &result);
            if(NULL != presult)
            {
                result = *presult;
                strftime(buffer, sizeof(buffer), str_fmt.c_str(), &result);
            }
        }
        return std::string(buffer);
    }
}

