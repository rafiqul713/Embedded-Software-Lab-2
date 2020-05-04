#include <avr/io.h>
//#define F_CPU 12000000UL
#include <util/delay.h>
#define BAUD 19200UL
#define BAUDRATE (F_CPU/(16*BAUD)-1)
#include <util/setbaud.h>



void uart_init();
void uart_transmission(unsigned char);
unsigned char uart_receive();

void uart_init(){

    //set baud rate
    /*
        UBRR is a 16 bit register which is used to set the
        baud rate of UART
    */
    UBRR0H =  (unsigned char)BAUDRATE>>8;
    UBRR0L =  (unsigned char)BAUDRATE;
    /*
         UCSRB (UART control and status Register B)
         is used to control UART transmission and receiption

    */
    //Transmitter and Receiver is Enabled
    /* TXEN bit 1 Enable Transmission 0 Disable Transmission*/
    /* RXEN bit 1 Enable Reception 0 Disable Reception*/
    UCSR0B|= (1<<TXEN0)|(1<<RXEN0);


    //Used for 8 bit data format
    /* UCSZ0 and UCSZ1 are used to select the number of data bits
     to be transmitter.
     URSEL(UART register select) is used to select between accessing the UCSRC
     or UBRRH register. Because UCSRC and UBRRH share the same I/O
     */
    UCSR0C|= (1<<USBS0)|(3<<UCSZ00); //Asynchornous mode


}

void uart_transmission(unsigned char send_data){
    /*
        UCSRA(USART control and status register A) is a 8 bit register
        UDRE (USART data register Empty) flag indicate if the transmit
        buffer(UDR) is ready to receive new data.
        1 means Buffer is Empty 0 means not Empty
    */
    //Wait until the register is free
    while(!(UCSR0A & (1<<UDRE0)));
    //write the new data in Transmit Buffer (UDR)
    UDR0= send_data;

 }

 unsigned char uart_receive(){
    /*
        RXC flag is set by the CPU when there are unread data in the receive
        buffer and is cleared by the CPU when the receive buffer is empty
    */
    // Wait until the data is received
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0; // UDR return 8 bit
 }
