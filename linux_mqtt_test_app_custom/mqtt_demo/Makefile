
CC=arm-linux-gnueabi-gcc
CFLAGS = -Wall -O2
LIBS = -lpaho-mqtt3c

.PHONY: all

all: mqtt_demo

mqtt_demo: mqtt_demo.o cJSON.o 
	$(CC) -o mqtt_demo mqtt_demo.o cJSON.o $(LIBS) 

OBJS = mqtt_demo.o cJSON.o 
	
$(OBJS):%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
.PHONY: clean
clean:
	-rm -v *.o mqtt_demo