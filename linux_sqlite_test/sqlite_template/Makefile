SRCS  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))
  
TARGET  := executable_file 
CC      := gcc
LIBS    := -L ../installed_x86tmp/lib/
LDFLAGS := -l sqlite3 -l pthread
DEFINES :=
INCLUDE := -I ../installed_x86tmp/include/
CFLAGS  := -g -Wall $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H
  
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
