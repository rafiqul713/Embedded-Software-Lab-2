#pragma once
#include<avr/io.h>
#include "Timer_Interrupt_Handler.h"
#include "PIN_Change_Interrupt_Handler.h"

void LED_blink();
void LED_off();
void clock_signal_change();
void clock_signal_receive();

//LED blinking indicate that signal is received
void LED_blink(){
    PORTB^=(1<<PB3);
}

//Changing clock signal
void clock_signal_change(){
    //if clock signal is HIGH
    //then make it LOW
    if(PINB & (1<<PB4)){
        PORTB&=~(1<<PB4);
    }
    //if clock signal is LOW
    //then make it HIGH
	else{
        PORTB|=(1<<PB4);
    }

}

//Receive clock signal
void clock_signal_receive(){
    LED_blink();
}


