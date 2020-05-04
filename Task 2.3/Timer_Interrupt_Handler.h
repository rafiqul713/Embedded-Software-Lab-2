#pragma once // allows preprocessor to include header file when needed otherwise ignore include
#include<avr/io.h>
#include<avr/interrupt.h>

//#include "UART_Handler.h"
void timer_interrupt_initialization();
void startTimer0();
volatile uint8_t counter;

void timer_interrupt_initialization(){
    /*
      TIMSK0 Timer counter interrupt mask register has OCIE0B,
      OCIE0A, TOIE0 bit. To set Timer 0 Interrupt need to set TOIE0
    */
    TIMSK0|=(1<<TOIE0);
    TCNT0=0;
    //Enable global Interrupt
    sei();

}

void startTimer0(){
    /*
         TCCR0A and TCCR0B Timer counter control register A and B
    */
    TCNT0=0;
    //Set prescalar 1024 and start the timer
    TCCR0B|=(1<<CS02)|(1<<CS00);
}




//Here ISR handle timer 0 overflow interrupt
ISR (TIMER0_OVF_vect) {
    counter++;
    /*
        16 MHz= 16000000Hz/1024 prescale = 15625 Hz
        Period= 1/15625= 0.000064 microsecond = 0.064 milisecond
        Timer 0 is 8 bit timer. so it can store 0 to 255.
        0.064*256 = 16.385 milisecond Overflow will be occured in timer 0
        To generate a delay of 1 second which is 1000 milisecond
        (1000/16.385)= 61.03 or 62

    */
    while(counter>=62){
        uart_transmission('I');
        counter=0;
    }

}









