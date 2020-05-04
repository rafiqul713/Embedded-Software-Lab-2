#pragma once
#include<avr/io.h>
#include "Timer_Interrupt_Handler.h"
#include "PIN_Change_Interrupt_Handler.h"

void LED_blink_for_clock_signal_receive();
void LED_blink_for_data_signal_receive();
void LED_off();
void clock_signal_change();
void clock_signal_receive();
int data_send();
int data_receive();
void log_msg(char *);

//LED blinking indicate that signal is received
void LED_blink_for_clock_signal_receive(){
    PORTB^=(1<<PB3);
}

void LED_blink_for_data_signal_receive(){
    PORTB^=(1<<PB2);
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
    LED_blink_for_clock_signal_receive();
}


int data_send(){
    //if data send signal is HIGH
    //then make it LOW
    if(PINB & (1<<PB5)){
        PORTB&=~(1<<PB5);
        return 0;
    }
    //if data send signal is LOW
    //then make it HIGH
	else{
        PORTB|=(1<<PB5);
        return 1;
    }
}

int data_receive(){
    if(PIND&(1<<PD5)){
       return 1;
    }
    else{
        return 0;
    }
}

void log_msg(char *str){
    int i;
    for(i=0;str[i]!='\0';i++){
        uart_transmission(str[i]);
    }
}
