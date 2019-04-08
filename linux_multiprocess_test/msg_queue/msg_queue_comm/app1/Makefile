SRC_PATH = ./
DIRS = $(shell find $(SRC_PATH) -maxdepth 5 -type d)



#DIRS = DBASE PRTC STD USR .

TARGET = app1



CC = gcc
CFLAGS = -O2 
CFLAGS += $(patsubst %,-I%,$(DIRS))

LDFLAGS := -lpthread

FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)
	-$(RM) $(OBJS)

clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
