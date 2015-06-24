
TARGET = libiopccfg.so

CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += 

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread 
LDFLAGS += -ljson-c

INCLUDES += 

SRC = 
SRC += main.c

include Makefile.include
