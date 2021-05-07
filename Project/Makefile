

CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c


all:wake.elf

#additional rules for files
wake.elf: ${COMMON_OBJECTS} wake.o stateMachines.o led.o p1_interrupt_handler.o switches.o buzzer.o  wdInterruptHandler.o ../lib/libTimer.a 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: wake.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf *~ *#
led.o:  led.h

switches.o:  switches.h 


wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h  stateMachines.h switches.h


buzzer.o:  buzzer.h
