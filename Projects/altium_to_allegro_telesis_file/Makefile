# Makefile
#
# Created on: 2014-08-09
#     Author: cya
#

# define the project name, and the cpu type
PRJ = altium_to_allegro_telesis_file

# specify tools to build this project
PREFIX = 
CC   = $(PREFIX)gcc
AS   = $(PREFIX)gcc
LD   = $(PREFIX)gcc

# list C source files here
SRC  = altium_to_allegro_telesis_file.c
       
# list ASM source files here
ASRC = 

OBJS = $(ASRC:.s=.o) $(SRC:.c=.o) 

# list libs dir here
LIBDIR = 

# list build tools options here
CCFLAGS =  -c     
ASFLAGS =  -c
LDFLAGS = 

#
# makefile rules
#

all: $(PRJ).exe

$(PRJ).exe: $(OBJS)
	$(LD) $(LDFLAGS)  $(OBJS) -o $@

%.o : %.c
	$(CC)  $(CCFLAGS) $< -o $@
	
%.o : %.s
	$(AS)  $(ASFLAGS) $< -o $@
	
clean:
	rm  $(PRJ).exe $(OBJS) 
	

