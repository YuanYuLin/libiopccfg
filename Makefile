
TARGET = libiopccfg.so

CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += 
CFLAGS += -I/usr/include/json-c
LDFLAGS += -L/usr/lib/x86_64-linux-gnu/
LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread 
LDFLAGS += -ljson-c

INCLUDES += 

SRC = 
SRC += iopccfg.c

include Makefile.include
