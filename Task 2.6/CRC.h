#include<avr/io.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char polynomial[33]={"11101101101110001000001100100000"}; //0xEDB88320
char crc[33];
char *crc_creation(char payload[]);

char *crc_creation(char payload[]){
    int i,j;
    int polynomialLength=strlen(polynomial);
    int payloadLength=strlen(payload);
    int encodedLength=payloadLength+polynomialLength-1;
    for(i=0;i<8;i++){
        crc[i]=payload[i];
    }
    for(i=payloadLength;i<encodedLength;i++){
        crc[i]='0';
    }

    i=0;
    while(i<=encodedLength-polynomialLength){
        for(j=0;j<polynomialLength;j++){
            if(crc[i+j]==polynomial[j]){
                crc[i+j]='0';
            }
            else{
                crc[i+j]= '1';
            }
        }
    for(;i<encodedLength && crc[i]!='1';i++);

    }

    return crc;
}



