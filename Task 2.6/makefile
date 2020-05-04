MCU		= atmega328p   #Microcontroller Unit
TARGET 		= main	       #Target file name without extension
SOURCES		= main.c       #Source file 
PROGRAMMER	= gpio	       #set programmer 
PORT 		= /dev/ttyAMA0 #set port for UART	
BAUD 		= 9600	       #serial port is capable to transfer 9600 bit/second
FORMAT		= ihex 	       #output format ihex [other format binary]
CC		= avr-gcc      #compiler 
OBJECTS 	= $(TARGET).o
OPTIMIZE	= s            #[s=optimize for size and 0=stop optimization] 
LDFLAGS		= -Wl,-gc-sections -Wl #Linker Option 

#CFLAGS is used as compiler option
#-g : generate debugging information 
#-O : optimization level 
#-Wall : warning level
#-Werror: Error level
CFLAGS 		= -g -c -Werror -Wall -O$(OPTIMIZE) 
#at first clean .o, .elf, .hex files then call: hex and program
all : clean hex program  
hex : $(TARGET).hex
$(TARGET).elf : $(OBJECTS) #create .elf file from object file
	$(CC) $(LDFLAGS) -mmcu=$(MCU) $(OBJECTS) -o $(TARGET).elf
#create .hex file from .elf file
$(TARGET).hex : $(TARGET).elf 
	#objcopy copies binary file 
	#implicit rule
	#$@ name of the target file
	#$< name of the first prerequisite .elf
	#This rule state that, .hex is generated from .elf
	avr-objcopy -O $(FORMAT) $< $@ 
#suffix: c.o
#make .o file from .c file 	
.c.o : 
	$(CC) $(CFLAGS) -mmcu=$(MCU) $< -o $@
program :
	#avrdude command line tool
	#-p Processing Unit
	#-P Port 
	#-b data rate/baud
	#-c configuration file: programmer
	#-e delete the content of ROM and EEPROM
	#-U memtype:op:filename[:format] here, memtype: flash memory operation: write	
	avrdude -p $(MCU) -P $(PORT) -b $(BAUD) -c $(PROGRAMMER) -e -U flash:w:$(TARGET).hex:a
clean :
	#remove file which have .o, .elf, .hex extension
	rm -rf *.o *.elf *.hex
