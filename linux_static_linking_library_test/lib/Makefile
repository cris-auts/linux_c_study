SRC_PATH = .
DIRS = $(shell find $(SRC_PATH) -maxdepth 5 -type d)



#DIRS = DBASE PRTC STD USR .

TARGET = libscomms.a



CC = gcc
CFLAGS += $(patsubst %,-I%,$(DIRS))

LDFLAGS := -l sqlite3 -l pthread -lpaho-mqtt3c

FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))
$(TARGET):$(OBJS)
	$(AR) cr -o $(TARGET) $(OBJS) 
	-$(RM) $(OBJS)
	sudo cp ./$(TARGET) /home/cris/My_Projects/linux_c_study/linux_static_linking_library_test/app/LIB -f
clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
