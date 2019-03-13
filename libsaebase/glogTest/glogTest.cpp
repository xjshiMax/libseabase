// glogTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <iostream>
using namespace std;
 
#include <glog/logging.h>
#pragma comment(lib, "libglog.lib")
 
 int main(int argc, char **argv)
 {
	 FLAGS_log_dir = "E:\\";
	 google::InitGoogleLogging("infosun");
	 google::SetLogDestination(google::GLOG_INFO, "E:\\Logs\\INFO_");
	 google::SetStderrLogging(google::GLOG_INFO);
	 google::SetLogFilenameExtension("log_");
	 FLAGS_colorlogtostderr = true;  // Set log color
	 FLAGS_logbufsecs = 0;  // Set log output speed(s)
	 FLAGS_max_log_size = 1024;  // Set max log file size
	 FLAGS_stop_logging_if_full_disk = true;  // If disk is full
	 char str[20] = "hello log!";
	 LOG(INFO) << str;
	 string cStr = "hello google!";
	 LOG(INFO) << cStr;
	 LOG(INFO) << "info test" << "hello log!";  //���һ��Info��־
	 LOG(WARNING) << "warning test";  //���һ��Warning��־
	 LOG(ERROR) << "error test";  //���һ��Error��־
	 google::ShutdownGoogleLogging();
 
	     system("pause");
     return 0;
 }