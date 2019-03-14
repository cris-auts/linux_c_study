SRC_PATH = .
DIRS = $(shell find $(SRC_PATH) -maxdepth 5 -type d)



#DIRS = DBASE PRTC STD USR .

TARGET = test_app



CC = gcc
CFLAGS = -O2 
CFLAGS += $(patsubst %,-I%,$(DIRS))

LDFLAGS := -l sqlite3 -l pthread -lpaho-mqtt3c

FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, %.o, $(FILES))
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)
	-$(RM) $(OBJS)

clean:
	-$(RM) $(TARGET)
	-$(RM) $(OBJS)
