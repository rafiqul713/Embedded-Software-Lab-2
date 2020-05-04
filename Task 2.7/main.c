#define F_CPU 16000000UL
#include<avr/io.h>
#include "initialization.h"
//#include "UART_Handler.h"
#include "Timer_Interrupt_Handler.h"
#include "PIN_Change_Interrupt_Handler.h"
#include "Buffer.h"


int main(){
	//initialization
    portInitialization();
    pin_change_interrupt_initialization();
    uart_init();
    timer_initialization();
    sei();//global interrupt
    //Initialize value for frame 
    strcpy(senderFrame.preamble,predefined_preamble);
    strcpy(senderFrame.payloadSize,"01100000");
    strcpy(senderFrame.payload,"11000000");
    strcpy(predefined_preamble,"01111110");
    crc_creation(senderFrame.payload);

    while(1){

    }

}
