#pragma once
#include<avr/io.h>
#include<avr/interrupt.h>
#include "Layer1.h"
#include "UART_Handler.h"

char receive_buffer[0];
void pin_change_interrupt_initialization();
void clock_signal_receive();
int data_receive();
void log_msg();
void LED_blink_for_data_signal_receive();

//Initializing PIN change interrupt
void pin_change_interrupt_initialization(){
  //pin change interrupt control register
  PCICR|= (1<<PCIE2); // enabled PCINT[23:16] pin will cause an interrupt
  //pin change mask register 2
  PCMSK2|=(1<<PCINT20);//pin change interrupt for PD4 or clock receive signal
}

//PIN change interrupt service routine
ISR(PCINT2_vect){
  clock_signal_receive();//LED blink indicate clock signal receive
  log_msg("receiver: ");
  if(data_receive()==1){
    LED_blink_for_data_signal_receive();//LED blink indicate data signal receive
    receive_buffer[0]='1';
    uart_transmission(receive_buffer[0]);
  }
  else{
    receive_buffer[0]='0';
    uart_transmission(receive_buffer[0]);
  }
  uart_transmission('\r');
  uart_transmission('\n');

}


