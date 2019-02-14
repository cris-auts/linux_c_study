######################################
#
######################################
#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
SRCS  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))
  
#target you can change test to what you want
#目标文件名，输入任意你想要的执行文件名
TARGET  := executable_file 
  
#compile and lib parameter
#编译参数
CC      := gcc
LIBS    := -L ../installed_x86tmp/lib/
LDFLAGS := -l sqlite3
DEFINES :=
INCLUDE := -I ../installed_x86tmp/include/ 
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H
  
  
#i think you should do anything here
#下面的基本上不需要做任何改动了
.PHONY : objs clean rebuild
  
all : $(TARGET)
  
objs : $(OBJS)
  
rebuild: veryclean everything
                
clean :
	rm -rf *.so
	rm -fr *.o
	rm -fr $(TARGET)
  
$(TARGET) : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
