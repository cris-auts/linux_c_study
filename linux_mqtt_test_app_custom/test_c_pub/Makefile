.PHONY: clean

#CC = /usr/bin/arm-linux-gnueabi-gcc
CC = gcc
RM = rm

TARGET = test_c_pub
INCS = $(wildcard *.h)
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

LIBS    := -lpaho-mqtt3a

$(TARGET) : $(OBJS) $(INCS)
	$(CC) -o $@ $(OBJS) $(LIBS)
%.o: %.c $(INCS)
	$(CC) -o $@ -c $< 
clean:
	$(RM) -fr $(TARGET) $(OBJS)

