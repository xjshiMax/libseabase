//#ifdef WIN32
#include "../include/ExftpClient.h"
#include "../../base/curl7.65.1/windows/x86-debug-static/include/curl/curl.h"
#pragma comment(lib,"E:/aaa-shi/libseabase/base/curl7.65.1/windows/x86-debug-static/lib/libcurl_a_debug.lib")
//#else
//#endif
namespace SEABASE{

    static size_t FetchFiles(void *buffer, size_t size, size_t nmemb, void *stream)
    {
        struct FtpFile *out = (struct FtpFile *)stream;
        if (out && !out->stream) 
        {
            // open file for writing 
            out->stream = fopen(out->filename, "wb");
            if (!out->stream)
                return -1; // failure, can't open file to write
        }
        return fwrite(buffer, size, nmemb, out->stream);
    }
    // ---- common progress display ---- //
struct CustomProgress
{
    curl_off_t lastruntime; /* type depends on version, see above */
    CURL *curl;
};

// work for both download and upload
int progressCallback(void *p,
                     curl_off_t dltotal,   //需要下载总字节
                     curl_off_t dlnow,     //已经下载字节数
                     curl_off_t ultotal,   //将要上传总字节
                     curl_off_t ulnow)     //已经上传字节数
{
    struct CustomProgress *progress = (struct CustomProgress *)p;
    CURL *curl = progress->curl;
    curl_off_t curtime = 0;

    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &curtime);

    /* under certain circumstances it may be desirable for certain functionality
     to only run every N seconds, in order to do this the transaction time can
     be used */
    if ((curtime - progress->lastruntime) >= 3000000)
    {
        progress->lastruntime = curtime;
        printf("TOTAL TIME: %f \n", curtime);
    }

    // do something to display the progress
    printf("UP: %ld bytes of %ld bytes, DOWN: %ld bytes of %ld bytes \n", ulnow, ultotal, dlnow, dltotal);
    if (ultotal)
        printf("UP progress: %0.2f\n", float(ulnow / ultotal));
    if (dltotal)
        printf("DOWN progress: %0.2f\n", float(dlnow / dltotal));

    return 0;
}

// ---- upload related ---- //
// parse headers for Content-Length
size_t getContentLengthFunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int r;
    long len = 0;

    r = sscanf((const char*)ptr, "Content-Length: %ld\n", &len);
    if (r) /* Microsoft: we don't read the specs */
        *((long *) stream) = len;
    return size * nmemb;
}

// discard already downloaded data
size_t discardFunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
    return size * nmemb;
}

// read data to upload
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
    FILE *f = (FILE*)stream;
    size_t n;
    if (ferror(f))
        return CURL_READFUNC_ABORT;
    n = fread(ptr, size, nmemb, f) * size;
    return n;
}
    int ExftpClient::FTP_UpLoadFile(string remotepath,string localfilepath,int timeout,int trytimes)
    {
            curl_global_init(CURL_GLOBAL_ALL);
    CURL *curlhandle = curl_easy_init();

    // get user_key pair
    char user_key[1024] = {0};
    sprintf(user_key, "%s:%s", m_username.c_str(), m_password.c_str());

    FILE *file;
    long uploaded_len = 0;
    CURLcode ret = CURLE_GOT_NOTHING;
    file = fopen(localfilepath.c_str(), "rb");
    if (file == NULL) 
    {
        perror(NULL);
        return 0;
    }
    string remote_file_path=m_url+"/"+remotepath;
    curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curlhandle, CURLOPT_URL, remote_file_path.c_str());
    curl_easy_setopt(curlhandle, CURLOPT_USERPWD, user_key);
    if (timeout)
        curl_easy_setopt(curlhandle, CURLOPT_FTP_RESPONSE_TIMEOUT, timeout);
    curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getContentLengthFunc);
    curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &uploaded_len);
    curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, discardFunc);
    curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
    curl_easy_setopt(curlhandle, CURLOPT_READDATA, file);
    curl_easy_setopt(curlhandle, CURLOPT_FTPPORT, "-"); /* disable passive mode */
    curl_easy_setopt(curlhandle, CURLOPT_FTP_CREATE_MISSING_DIRS, 1L);

    // set upload progress
    curl_easy_setopt(curlhandle, CURLOPT_XFERINFOFUNCTION, progressCallback);
    struct CustomProgress prog;
    prog.curl=curlhandle;
    prog.lastruntime=0;
    curl_easy_setopt(curlhandle, CURLOPT_XFERINFODATA, &prog);
    curl_easy_setopt(curlhandle, CURLOPT_NOPROGRESS, 0);

//    curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L); // if set 1, debug mode will print some low level msg

    // upload: 断点续传
    for (int c = 0; (ret != CURLE_OK) && (c < trytimes); c++)
    {
        /* are we resuming? */
        if (c)
        { /* yes */
            /* determine the length of the file already written */
            /*
            * With NOBODY and NOHEADER, libcurl will issue a SIZE
            * command, but the only way to retrieve the result is
            * to parse the returned Content-Length header. Thus,
            * getContentLengthfunc(). We need discardfunc() above
            * because HEADER will dump the headers to stdout
            * without it.
            */
            curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 1L);
            curl_easy_setopt(curlhandle, CURLOPT_HEADER, 1L);
            ret = curl_easy_perform(curlhandle);
            if (ret != CURLE_OK)
                continue;
            curl_easy_setopt(curlhandle, CURLOPT_NOBODY, 0L);
            curl_easy_setopt(curlhandle, CURLOPT_HEADER, 0L);
            fseek(file, uploaded_len, SEEK_SET);
            curl_easy_setopt(curlhandle, CURLOPT_APPEND, 1L);
        }
        else
            curl_easy_setopt(curlhandle, CURLOPT_APPEND, 0L);

        ret = curl_easy_perform(curlhandle);
    }
    fclose(file);

//     int curl_state = 0;
//     if (ret == CURLE_OK)
//         curl_state = 1;
//     else
//     {
//         fprintf(stderr, "%s\n", curl_easy_strerror(ret));
//         curl_state = 0;
//     }

    // exit curl handle
    curl_easy_cleanup(curlhandle);
    curl_global_cleanup();

   // return curl_state;

        return 0;
    }
    int ExftpClient::FTP_UpLoad_Till()
    {
        return 0;
    }
    int ExftpClient::FTP_DownLoadFile( void *deststream,string srcfile)
    {
        CURL *curl;
        CURLcode res;
        FtpFile*ptemp=(FtpFile*)deststream;
        struct FtpFile ftpfile = {
            "b.jpg", // name to store the file as if succesful//
            NULL
        };
         if(deststream)
         {
             ftpfile.filename=ptemp->filename;
         }
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (curl) 
        {
            string fullpath=m_url+"/"+srcfile;
            string fulluserpwd=m_username+":"+m_password;
            curl_easy_setopt(curl, CURLOPT_URL,fullpath.c_str());
            curl_easy_setopt(curl, CURLOPT_USERPWD, fulluserpwd.c_str());

            // Define our callback to get called when there's data to be written //
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FetchFiles);
            // Set a pointer to our struct to pass to the callback //
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);

            // Switch on full protocol/debug output //
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

            res = curl_easy_perform(curl);

            // always cleanup 
            curl_easy_cleanup(curl);

            if (CURLE_OK != res) 
            {
                //we failed 
                fprintf(stderr, "curl told us %d\n", res);
            }
        }

        if (ftpfile.stream)
            fclose(ftpfile.stream); // close the local file 

        curl_global_cleanup();
        return 0;
    }
    int ExftpClient::FPT_GetProcessPoint()
    {
        return 0;
    }

     string ExftpClient::inner_getsrcFullPath()
     {
         return "";
     }
}