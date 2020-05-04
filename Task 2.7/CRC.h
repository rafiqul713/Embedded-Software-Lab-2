#include<avr/io.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char polynomial[33]={"11101101101110001000001100100000"}; //0xEDB88320
char crc[33];
char *crc_creation(char payload[]);
int crc_check(char encodedMsg[]);



char *crc_creation(char payload[]){
    int i,j;
    //char *remainder=(char*)malloc(32*sizeof(char));

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


int crc_check(char encodedMsg[]){
   int i,j;
   char *receivedMsg=(char*)malloc(41*sizeof(char));
   for(i=0;i<41;i++){
    receivedMsg[i]=encodedMsg[i];
   }
   int encodedLength=strlen(encodedMsg);
   int polynomialLength=strlen(polynomial);

   i=0;
   while(i<=encodedLength-polynomialLength){
      for(j=0;j<polynomialLength;j++){
         if(receivedMsg[i+j]==polynomial[j]){
            receivedMsg[i+j]='0';
         }
         else{
            receivedMsg[i+j]= '1';
         }
      }
      for(;i<encodedLength && receivedMsg[i]!='1';i++);

    }
    //Check: if 0 then there is no error. Otherwise error.
    for(i=0;i<encodedLength;i++){
        if(receivedMsg[i]!='0'){
           return 1;
        }
    }
    return 0;
}

