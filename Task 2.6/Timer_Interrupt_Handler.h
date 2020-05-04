#pragma once // alows preprocessor to include header file when needed otherwise ignore include
#include<avr/io.h>
#include<avr/interrupt.h>
//#include "UART_Handler.h"
#include "Layer1.h"
#include "Layer2.h"
#include "Buffer.h"

int TransmitIndex=0;
int sender_flag=2;
void timer_interrupt_initialization();
int Compare_A=0;
int Compare_B=0;
void timer_initialization(){
	TIMSK0 |= (1 << OCIE0A);// Compare match A
	TIMSK0 |= (1 << OCIE0B);// Compare match B
	//When use CTC mode the counter is cleared to zero
    //when the counter value (TCNT0) match with OCR0A

	TCCR0A |= (1 << WGM01);//  CTC mode
	TCCR0B |= (1 << CS02);
	//Compare Register A  contains an 8-bit
    // value that is continuously compared with
    //the counter value (TCNT0).
	OCR0A = 0xF8; //set value to count till F8 or 248
	//here, 1/(clock/prescalar)*OCR0A value)
    //or, 1/((16000000/256) * 248) = 1/(62500*248)= 1/252
    //1/252 = 0.003968254 second per cycle



}

ISR(TIMER0_COMPA_vect){

	Compare_A=Compare_A+1;
	if(Compare_A>100){
        Compare_A=0;
        if(sender_flag==1){
            //showLog("Transmit CRC generation:");
            crc_creation(senderFrame.payload);
            //showData(crc,32);
            TransmitIndex=0;
            sender_flag=2;
        }
        else if(sender_flag==2){
            if(readBitstream(predefined_preamble,TransmitIndex)){
                tranmit_1();

            }

            else if(!readBitstream(predefined_preamble,TransmitIndex)){
                tranmit_0();

            }

            TransmitIndex++;
            if(TransmitIndex>=8){

                showLog("Transmit preamble: ");
                showData(predefined_preamble,8);

                TransmitIndex=0;
                sender_flag=3;
            }
        }

        else if(sender_flag==3){
            if(readBitstream(crc,TransmitIndex)){
            tranmit_1();

            }

            else if(!readBitstream(crc,TransmitIndex)){
            tranmit_0();

            }

            TransmitIndex++;
            if(TransmitIndex>=32){
                showLog("Transmit CRC: ");
                showData(crc,32);
                TransmitIndex=0;
                sender_flag=4;

            }
        }

        else if(sender_flag==4){

            if(readBitstream(senderFrame.payloadSize,TransmitIndex)){
            tranmit_1();

            }

            else if(!readBitstream(senderFrame.payloadSize,TransmitIndex)){
            tranmit_0();

            }

            TransmitIndex++;
            if(TransmitIndex>8){
                showLog("Transmit payload size: ");
                showData(senderFrame.payloadSize,8);
                TransmitIndex=0;
                sender_flag=5;
            }
        }


        else if(sender_flag==5){

            if(readBitstream(senderFrame.payload,TransmitIndex)){
            tranmit_1();

            }

            else if(!readBitstream(senderFrame.payloadSize,TransmitIndex)){
            tranmit_0();

            }

            TransmitIndex++;
            if(TransmitIndex>8){
                showLog("Transmit payload: ");
                showData(senderFrame.payload,8);
                TransmitIndex=0;
                sender_flag=1;
            }
        }


    }

}


ISR(TIMER0_COMPB_vect){
   Compare_B=Compare_B+1;
   if(Compare_B>100){
      Compare_B=0;
      clock_signal_change();
    }
}
