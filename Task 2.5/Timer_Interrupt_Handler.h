#pragma once // alows preprocessor to include header file when needed otherwise ignore include
#include<avr/io.h>
#include<avr/interrupt.h>
#include "Layer1.h"

int Compare_A=0;
int Compare_B=0;
char send_buffer[1];
void timer_interrupt_initialization();
void clock_signal_change();
int data_send();
//Timer initialization for Timer 0 Compare vector A
//and Timer 0 Compare vector B
void timer_interrupt_initialization(){
	TIMSK0 |= (1 << OCIE0A);// Compare match A
	TIMSK0 |= (1 << OCIE0B);// Compare match B
    //When use CTC mode the counter is cleared to zero 
    //when the counter value (TCNT0) match with OCR0A
	TCCR0A |= (1 << WGM01);// CTC mode 
	TCCR0B |= (1 << CS02); // Clock/256 = 46875
    //Compare Register A  contains an 8-bit
    // value that is continuously compared with 
    //the counter value (TCNT0).
	OCR0A = 0xF8; //set value to count till F8 or 248  
    //here, 1/(clock/prescalar)*OCR0A value)
    //or, 1/((16000000/256) * 248) = 1/(62500*248)= 1/252
    //1/252 = 0.003968254 second per cycle

}

//Timer0 with compare vector A 
ISR(TIMER0_COMPA_vect){
    Compare_A++;
    while(Compare_A>100){
        clock_signal_change();
        Compare_A=0;
    }

}

//Timer0 with compare vector B
ISR(TIMER0_COMPB_vect){
    Compare_B++;
    while(Compare_B>100){
        if(data_send()==1){
            send_buffer[0]='1';
        }
        else{
            send_buffer[0]='0';
        }
        Compare_B=0;
    }

}
