VERSION = 1.0.0
TARGET = test_v$(VERSION)
CROSS = 



TOP_PATH = $(shell pwd)





SRCS  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRCS)))

CC      := $(CROSS)gcc
LIBS_PATH = -L./
LDFLAGS := -l sqlite3 -l pthread -lpaho-mqtt3c
DEFINES :=
INCLUDES := -I./ 
CFLAGS  := -g -Wall $(DEFINES) $(INCLUDES)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H
RM = rm -rf  


.PHONY : objs clean rebuild
  
all : $(TARGET)
                
clean :
	$(RM) $(TARGET) *.o *.so
  
$(TARGET) : $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS_PATH)
