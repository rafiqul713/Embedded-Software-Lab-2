#define F_CPU 16000000UL // set frequency
#include<avr/io.h>
#include "initialization.h"
//#include "Layer1.h"
//#include "UART_Handler.h"
#include "Timer_Interrupt_Handler.h"
#include "PIN_Change_Interrupt_Handler.h"

int main(){

    portInitialization();
    timer_interrupt_initialization();
    pin_change_interrupt_initialization();
    uart_initialization();
    sei(); //global interrupt
    while(1){
        //endless loop
        //repeatedly transmit and receive signal
    }


}



