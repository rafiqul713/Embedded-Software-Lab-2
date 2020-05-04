#define F_CPU 16000000UL // set frequency 
#include<avr/io.h>
#include<util/delay.h>
#include "initialization.h"
#include "UART_Handler.h"
#include "Timer_Interrupt_Handler.h"


int main(){
    portInitialization();
    uart_init();
    timer_interrupt_initialization();
    startTimer0();
    while(1){

        uart_transmission('M');
        _delay_ms(1000);

    }

}



