#pragma once
#include<avr/io.h>
#include<avr/interrupt.h>
#include "Layer1.h"
#include "Buffer.h"
#include "UART_Handler.h"
#include "Layer2.h"
#include "Buffer.h"

int ReceiverIndex=0;
int receiver_flag=1;
void pin_change_interrupt_initialization();


//Initializing PIN change interrupt
void pin_change_interrupt_initialization(){
  //pin change interrupt control register
  PCICR|= (1<<PCIE2); // enabled PCINT[23:16] pin will cause an interrupt
  //pin change mask register 2
  PCMSK2|=(1<<PCINT20);//pin change interrupt for PD4 or clock receive signal
}


ISR(PCINT2_vect){

}






