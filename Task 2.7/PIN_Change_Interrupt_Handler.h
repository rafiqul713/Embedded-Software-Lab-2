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

    if(receiver_flag==1){


        if(data_receive()){
            recvPrem[ReceiverIndex]='1';
        }
        else{
            recvPrem[ReceiverIndex]='0';
        }
        ReceiverIndex++;

        if(ReceiverIndex>=8){
            showLog("Received preamble: ");
            showData(recvPrem,8);
            if(compare(recvPrem,predefined_preamble,8)){
                showLog("Correct Preamble");
                receiver_flag=2;

            }

            ReceiverIndex=0;

        }
    }

    else if(receiver_flag==2){
        if(data_receive()){
            recvCRC[ReceiverIndex]='1';

        }
        else{
            recvCRC[ReceiverIndex]='0';

        }
        ReceiverIndex++;

        if(ReceiverIndex>=32){
            showLog("Received CRC: ");
            showData(recvCRC,32);
            ReceiverIndex=0;
            receiver_flag=3;

        }
    }

    else if(receiver_flag==3){
        if(data_receive()){
            recvPayloadSize[ReceiverIndex]='1';

        }
        else{
            recvPayloadSize[ReceiverIndex]='0';
        }
        ReceiverIndex++;

        if(ReceiverIndex>8){
            showLog("Received payload size: ");
            showData(recvPayloadSize,8);
            ReceiverIndex=0;
            receiver_flag=4;

        }
    }

    else if(receiver_flag==4){
        if(data_receive()){
            recvPayload[ReceiverIndex]='1';

        }
        else{
            recvPayload[ReceiverIndex]='0';
        }
        ReceiverIndex++;

        if(ReceiverIndex>8){
            showLog("Received payload: ");
            showData(recvPayload,8);
            ReceiverIndex=0;
            receiver_flag=5;

        }
    }

    else if(receiver_flag==5){
        crc_creation(recvPayload);
        if(compare(crc,recvCRC,32)){
            showLog("Correct CRC");
            showLog("Communication success........!");
        }

        else{
            showLog("Wrong CRC");
        }
        ReceiverIndex=0;
        receiver_flag=1;


    }

}






