BINNAME=tcpserver
basepath=../../output

INC_PATH=-I./
INC_PATH += -I$(basepath)/include

LIB_PATH = -L$(basepath)/lib/linux

LIB= -lseabase
CFLAGS=-g -Wall
SOURCE= tcpserver.cpp

$(BINNAME):$(SOURCE)
	g++ -o $@ $^ $(CFLAGS) $(INC_PATH) $(LIB_PATH) $(LIB)