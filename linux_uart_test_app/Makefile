.PHONY: clean

#CC = /usr/bin/arm-linux-gnueabi-gcc
CC = gcc
RM = rm

TARGET = uart_test_app
INCS = $(wildcard *.h)
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

$(TARGET) : $(OBJS) $(INCS)
	$(CC) -o $@ $(OBJS)
%.o: %.c $(INCS)
	$(CC) -o $@ -c $< 
clean:
	$(RM) -fr $(TARGET) $(OBJS)

