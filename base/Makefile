LIBNAME = libseabase

INC_PATH = -I.
INC_PATH = -I./include
LIB_PATH = 
VERSION="1.0.0"

LIB = -lpthread
CFLAGS=-Wall -g -fPIC \
		-DVERSION=\"$(VERSION)\"
		
SOURCES = $(wildcard src/*.cpp)

OBJS = $(patsubst %.cpp ,%.o,$(SOURCES))

CXX =g++
OUTPUT_PATH=../output/lib/linux/

#make all ----------------------------#

outputdir: output
	if [ ! -d $(OUTPUT_PATH) ];then mkdir -p $(OUTPUT_PATH);fi
	
output:$(OBJS)
	ar -cr $(LIBNAME).a  $(OBJS) 
	$(CXX) -shared $(CFLAGS) -o $(LIBNAME).so $(OBJS) $(INC_PATH) -lpthread
	cp $(LIBNAME).* $(OUTPUT_PATH)
	
$(OBJS):
	$(CXX) $(CFLAGS) -o $@ $(INC_PATH) -c $<
	
clear: 
	rm -f $(OBJS)
	rm -f *.a
	rm -f $(LIBNAME)
	rm -rf $(OUTPUT_PATH)
	