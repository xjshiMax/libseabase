// glogTest.cpp : 定义控制台应用程序的入口点。
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
	 //FLAGS_minloglevel = loglevel;
	 char str[20] = "hello log!";
	 LOG(INFO) << str;
	 string cStr = "hello google!";
	 LOG(INFO) << cStr;
	 LOG(INFO) << "info test" << "hello log!";  //输出一个Info日志
	 LOG(WARNING) << "warning test";  //输出一个Warning日志
	 LOG(ERROR) << "error test";  //输出一个Error日志
	 google::ShutdownGoogleLogging();
 
	     system("pause");
     return 0;
 }