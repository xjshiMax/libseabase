INC_PATH=-I.
INC_PATH+= -I../../ExAppOnbase/include
INC_PATH+= -I../..
INC_PATH+= -I../../base/openssl/include
LIB= -L../../output/lib/linux -lseabase
LIB+= -L../../base/openssl/lib/linux/lib -lcrypto
LIB+= -L../../base/sqlite3/lib/linux -lsqlite3
LIB+= -lpthread -ldl
CFLAGS=-Wall -g
SOURCES = $(wildcard *.cpp ../../ExAppOnbase/src/*.cpp)

OBJS = $(patsubst %.cpp ,%.o,$(SOURCES))
OUTPUT_PATH=../../output/lib/linux
#make all------------

outputdir:output
	if [ ! -d $(OUTPUT_PATH) ]; then mkdir -p $(OUTPUT_PATH);fi
	
output:$(OBJS)
	g++ -o modulecom $(OBJS) $(CFLAGS) $(INC_PATH) $(LIB)
	cp modulecom $(OUTPUT_PATH)
clear:
		rm -f $(OBJS)
		rm -f modulecom