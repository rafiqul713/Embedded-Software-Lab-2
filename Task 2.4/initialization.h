#include<avr/io.h>
#include<util/delay.h>

void portInitialization(){
    //Receive PIN configuration
    DDRD&=~(1<<PD4);//Clock Receive
    DDRD&=~(1<<PD5);//Data Receive
    //Send PIN configuration
    DDRB|=(1<<PB4);//Clock Send
    DDRB|=(1<<PB5);//Data Send
    //LED output
    DDRB|=(1<<PB3);

}


