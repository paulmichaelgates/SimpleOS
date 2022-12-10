OBJECTS=task/* util/* boot/* drivers/watchdog/* io/* debug/*
MAP=temp.map
MAKEFILE=Makefile

ifeq ($(OS),Windows_NT)
	ifeq ($(shell uname -o),Cygwin)
		RM= rm -rf
	else
		RM= del /q
	endif
else
	RM= rm -rf 
endif

GCC_DIR = $(abspath $(dir $(lastword $(MAKEFILE)))/tools/msp430-gcc/bin)
SUPPORT_FILE_DIRECTORY = $(abspath $(dir $(lastword $(MAKEFILE)))/tools/msp430-gcc/include)

# Please set your device here
DEVICE  = MSP430FR2355
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb

# modules
UTIL 	= util
TASK 	= task
WDG		= drivers/watchdog
IO		= io
DEBUG 	= debug

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -I $(UTIL) -I $(TASK) -I $(WDG) -I $(IO) -I $(DEBUG) -mmcu=$(DEVICE) -Og -Wall -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -Wl,-Map,$(MAP),--gc-sections 

all: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $? -o $(DEVICE).out

clean: 
	$(RM) $(OBJECTS)
	$(RM) $(MAP)
	$(RM) *.out
	
debug: all
	$(GDB) $(DEVICE).out
