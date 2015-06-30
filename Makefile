
TARGET = libiopccfg.so

CFLAGS += -I$(SDKSTAGE)/usr/include/json-c
CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += 

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread 
LDFLAGS += -ljson-c

SRC = 
SRC += show_cfg.c
SRC += show_value.c

include Makefile.include
