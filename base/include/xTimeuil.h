//2019/4/18
//xjshi ʱ������ڼ���
#include < inttypes.h>

namespace SEABASE{

#ifdef _WIN32
	struct timezone 
	{
		int  tz_minuteswest; /* minutes W of Greenwich */
		int  tz_dsttime;     /* type of dst correction */
	};

#endif
	    class xTimeUtil {
    public:
        /**
         * @brief get_timestamp_s ��ȡʱ������룩
         *
         * @return ���ش�Epoch������������
         */
        static uint64_t get_timestamp_s();

        /**
         * @brief get_timestamp_ms ��ȡʱ��������룩
         *
         * @return ���ش�Epoch��������΢����
         */
        static uint64_t get_timestamp_ms();
        
        /**
         * @brief ��ȡ΢�뼶ʱ���
         *
         * @return  uint64_t 
         * @retval   
        **/
        static uint64_t get_timestamp_us();

        /**
         * @brief safe_sleep_s ֧���жϵ�sleep���룩
         *
         * @param second ˯�ߵ�����
         */
        static void safe_sleep_s(uint32_t second);

        /**
         * @brief safe_sleep_ms ֧���жϵ�sleep�����룩
         *
         * @param millisecond ˯�ߵĺ�����
         */
        static void safe_sleep_ms(uint32_t millisecond);

        /**
         * @brief format_datetime_str ��ʱ�����ʽ��
         *
         * @param millisecond ��Epoch�������ĺ�����
         *
         * @return ʱ����ַ���
         */
        static std::string format_datetime_str(uint64_t millisecond);

#ifndef _WIN32
//        struct ::timespec;
        /**
         * @brief get_abs_timespec ��ȡ�ӵ�ǰʱ��� milliSeconds �����ľ���ʱ��
         *
         * @param ts ��ž���ʱ��
         * @param millisecond ��ǰ��ĺ�����
         *
         * @return �ɹ�����0
         */
        static int32_t get_abs_timespec(struct timespec* ts, int32_t millisecond);
#endif

        /**
         * @brief strftimeval ��struct timevalת��Ϊ�ַ�����ʽ����ʽΪ"YYYY-MM-DD HH:mm::SS.xxx"
         *
         * @param buffer [out] ���ջ��������Ƽ���������СΪ24���ֽڡ�
         * @param buflen ��������С
         * @param tv ��ת����struct timevalָ��
         *
         * @return ����д�뻺�������ַ�����������\0�������򷵻�-1
         */
        static int32_t strftimeval(char* buffer, int32_t buflen, const struct timeval* tv);

        /**
         * @brief get_date ��ȡ���ڴ� "YYYYMMDD"
         *
         * @return ���ڴ�
         */
        static std::string get_date();

        /**
         * @brief get_time ��ȡʱ�䴮 "HHmmSS.xxx"
         *
         * @return 
         */
        static std::string get_time();

        /**
         * @brief ��ȡ��ǰ���ڼ�
         *
         * @return  int32_t 
         * @retval   
        **/
        static int32_t get_day();

        /**
         * @brief ��ȡָ�����ڵ����ڼ�
         *
         * @param [in/out] time   : time_t
         * @return  int32_t 
         * @retval   
        **/
        static int32_t get_day( time_t time );

        /**
         * @brief ��ʽ����ǰʱ�䣬Ĭ�ϸ�ʽΪ��%Y%m%d-%H:%M:%S��
         *
         * @param [in/out] fmt   : const char*
         * @return  std::string 
        **/
        static std::string format_time(const char * fmt = NULL);

        /**
         * @brief ��ʽ��ָ��ʱ�䣬Ĭ�ϸ�ʽΪ��%Y%m%d-%H:%M:%S��
         *
         * @param [in/out] time   : time_t
         * @param [in/out] fmt   : const char*
         * @return  std::string 
        **/
        static std::string format_time(time_t time, const char * fmt = NULL);

        /**
         * @brief ��ʽ��ָ��ʱ�䣬Ĭ�ϸ�ʽΪ��%Y%m%d-%H:%M:%S��
         *
         * @param [in/out] time   : const struct timeval*
         * @param [in/out] fmt   : const char*
         * @return  std::string 
        **/
        static std::string format_time(const struct timeval* tv, const char * fmt = NULL);
		 
		/**
         * @brief ��ʽ��ָ��ʱ�䣬Ĭ�ϸ�ʽΪ��%Y%m%d-%H:%M:%S��
         *
         * @param [in/out] time   : const struct timeval*
         * @param [in/out] fmt   : const char*
         * @return  std::string 
        **/
		static int32_t gettimeofday(struct ::timeval *tv, struct timezone *tz);

#ifdef _WIN32
    private:
		/*__declspec(thread)*/ static FILETIME _ft;             /**< ��׼ʱ��    */
        /*__declspec(thread)*/ static LARGE_INTEGER _pform;     /**< ��׼ʱ���  */
#endif
    }; // end of class TimeUtil

}