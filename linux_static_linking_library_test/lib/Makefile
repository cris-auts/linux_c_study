SRC_PATH = .
DIRS = $(shell find $(SRC_PATH) -maxdepth 5 -type d)



#DIRS = DBASE PRTC STD USR .

TARGET = libscomm.a



CC = gcc
CFLAGS += $(patsubst %,-I%,$(DIRS))

LDFLAGS := -l sqlite3 -l pthread -lpaho-mqtt3c

FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))
$(TARGET):$(OBJS)
	$(AR) cr -o $(TARGET) $(OBJS) 
	-$(RM) $(OBJS)
	#please sudo cp ./$(TARGET) /usr/local/lib/
	#please sudo ln -s /usr/local/lib/libcomm.so.0.0.1   /usr/local/lib/libcomm.so
	#please sudo ldconfig
clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
