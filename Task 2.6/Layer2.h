#pragma once
#include<avr/io.h>
#include<stdio.h>
#include<string.h>
#include "CRC.h"
#include "Buffer.h"

int readBitstream(char bitStream[], int);
int data_receive();
void tranmit_1();
void tranmit_0();
int compare(char *, char *, int);
void showLog(char msg[]);
void showData(char msg[],int len);



//sender part
int readBitstream(char bitstream[], int index){

    if(bitstream[index]=='1'){
        return 1;
    }

    else{
        return 0;
    }

}

void showLog(char msg[]){
    int i=0;
    uart_transmission('\r');
    uart_transmission('\n');
    for(i=0;msg[i]!='\0';i++){
        uart_transmission(msg[i]);

    }

}

void showData(char msg[],int len){
    int i=0;

    for(i=0;i<len;i++){
        uart_transmission(msg[i]);

    }
    uart_transmission('\r');
    uart_transmission('\n');
}



void tranmit_1(){

    PORTB|=(1<<PB5);

}

void tranmit_0(){

    PORTB&=~(1<<PB5);
}



int data_receive(){
    if(PIND&(1<<PD5)){
       return 1;
    }
    else{
        return 0;
    }
}


int compare(char str1[],char str2[], int len){
    int i=0,counter=0;
    for(i=0;i<len;i++){
        if(str1[i]==str2[i]){
            counter++;
        }
    }

    if(counter==len){
        return 1;
    }
    else{
        return 0;
    }
    return 0;
}
