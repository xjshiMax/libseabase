#	libseabase project
#	author:xjshi
#	date:2020/12/21
#	
#	build example
#	mkdir build
#	cd build
#	cmake -G "Visual Studio 10" ..
#	start libsaebase.sln
#	windows: 
#		cmake .. 
#		cmake --build .
#	linux:
#		cmake ..
#		make

if (WIN32)
    cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
	ADD_DEFINITIONS(-Wall -DWIN32 -DWIN32_LEAN_AND_MEAN )
	#windows使用cmake编译，针对本项目添加的编译宏
	ADD_DEFINITIONS(-DCMAKE_COMPILE)
else()
    cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
endif()

project(libseabase)

# Winsock.
if(WIN32)
    set(CMAKE_EXTRA_INCLUDE_FILES winsock2.h ws2tcpip.h)
    set(CMAKE_REQUIRED_LIBRARIES  ws2_32.lib)
    set(CMAKE_REQUIRED_DEFINITIONS -FIwinsock2.h -FIws2tcpip.h)
endif()

#设置库头文件目录位置
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/base/include)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

#设置编译输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#设置引用目录
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${INCLUDE_DIR})
if(WIN32)
	include_directories(${PROJECT_SOURCE_DIR}/base/pthread/Pre-built.2/include)
	include_directories(${LIBRARY_OUTPUT_PATH}/Debug)
	link_directories(${PROJECT_SOURCE_DIR}/base/pthread/Pre-built.2/lib)
endif()

#设置依赖库名称
SET(DEPEN_LIBS pthread dl)

#依赖库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(LIB_S_DIR ${PROJECT_SOURCE_DIR}/base/src)
set(TCPSERVER_DIR ${PROJECT_SOURCE_DIR}/libsaebase/tcpserver)

aux_source_directory(${LIB_S_DIR} SOURCE_SEABASE)
aux_source_directory(${TCPSERVER_DIR} TCPSERVER)
aux_source_directory(${PROJECT_SOURCE_DIR}/ExAppOnbase/src ExLayerSource)


#动态库
add_library(seabase SHARED ${SOURCE_SEABASE})
add_library(seabase_static STATIC ${SOURCE_SEABASE})
if(WIN32)
#target_link_libraries(seabase ${DEPEN_LIBS})
else()
target_link_libraries(seabase ${DEPEN_LIBS})
endif()
#ExApplayer库
add_library(ExAppLayer ${ExLayerSource})
target_include_directories(ExAppLayer PUBLIC ${PROJECT_SOURCE_DIR}/ExAppOnbase/include)
target_link_libraries(ExAppLayer seabase_static)
if(WIN32)
	target_link_directories(ExAppLayer PUBLIC ${PROJECT_SOURCE_DIR}/base/curl7.65.1/windows/x86-debug-static/lib)
	target_link_libraries(ExAppLayer libcurl_a_debug)
endif()

#可执行程序
add_executable(tcpserver1 ${TCPSERVER})
target_link_libraries(tcpserver1 seabase_static )
#test/moduletest
add_executable(moduletest ${PROJECT_SOURCE_DIR}/test/moduletest/main.cpp)
target_link_libraries(moduletest ExAppLayer )





