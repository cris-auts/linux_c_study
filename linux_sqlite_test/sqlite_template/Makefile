SRCS  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))
  
TARGET  := executable_file 
CC      := gcc
LIBS    := 
LDFLAGS := -l sqlite3 -l pthread -lpaho-mqtt3c
DEFINES :=
INCLUDE := 
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
