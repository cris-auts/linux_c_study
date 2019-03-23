SRC_PATH = ./
DIRS = $(shell find $(SRC_PATH) -maxdepth 5 -type d)



#DIRS = DBASE PRTC STD USR .

TARGET = test_app


CC = gcc
CFLAGS = -Wall -g
CFLAGS += $(patsubst %,-I%,$(DIRS))

LDFLAGS := -Wl,-Bstatic -lscomm -Wl,-Bdynamic -lsqlite3 -lpthread -lpaho-mqtt3c -L./LIB

FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)
	-$(RM) $(OBJS)

clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
