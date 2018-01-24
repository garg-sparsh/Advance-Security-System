#define F_CPU 12000000UL //define clock speed of the MCU
#include <avr/io.h> // include avr header file
#include <util/delay.h> //include delay header file
#include"lcd_16.h" //include LCD header file
#include"lcd_16.c" //Include LCD c file
#include<string.h>
char stored_data[13]="4B0044A98224";
void USARTInit(unsigned int ubrr_value) //UART initialization function
{
UBRRL = ubrr_value;
UBRRH = 0;
UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
UCSRB=(1<<RXEN)|(1<<TXEN); // Enable Receiver & Transmitter
}
void wait(float x) //Wait function
{
for(int i=0;i<(int)(46*x);i++)
_delay_loop_2(0);
}
unsigned char USARTReadChar()
{

while(!(UCSRA & (1<<RXC))); // Wait till the receiving is not completed.
return UDR; // Return the received data
}
void usart_putstr( const unsigned char *str ) //String Function
{
for( ;*str != 0x00; )
{
USARTWriteChar( *str++ );
}
}
void USARTWriteChar(unsigned char data)
{
while(!(UCSRA & (1<<UDRE))); // Wait till the data register is not Empty.
UDR=data; // put the data to be transfer
}
void main() //main function
{
unsigned char data;
DDRC=0xFF; //Declare Port C as Output
DDRA=0xFF; //Declare Port A as output for LEDs
char stored_d[5]="Matched";
char stored_a[5]="Not Matched";
volatile char sentence[5];

USARTInit(77); //setting baud rate 9600

lcd_init(LCD_DISP_ON); //LCD initialization

lcd_puts("System is ready"); //Print the text on LCD
lcd_gotoxy(1,1); //Select the location of the text
lcd_puts("waiting for new msg"); //Print the text on LCD

wait(1);

int c=1,k;

USARTWriteChar('A'); //Send AT command to the GSM Modem

wait(1);
USARTWriteChar('T');
wait(1);
USARTWriteChar('\n\r');

wait(2);
USARTWriteChar('A'); // send AT+CMGF=1 to the GSM modem for changing the
msg format

USARTWriteChar('T');
USARTWriteChar('+');
USARTWriteChar('C');
USARTWriteChar('M');

USARTWriteChar('G');

USARTWriteChar('F');
USARTWriteChar('=');
USARTWriteChar('1');
USARTWriteChar('\n\r');

wait(2);
USARTWriteChar('A');
USARTWriteChar('T');
USARTWriteChar('+'); // Sending AT Command AT+CMGD=1 to the

modem

USARTWriteChar('C');
USARTWriteChar('M'); // to delete inbox msg. at position no.1
USARTWriteChar('G');
USARTWriteChar('D');
USARTWriteChar('=');
USARTWriteChar('1');
USARTWriteChar('\n\r');

wait(.5);
lcd_clrscr(); //clear screem
lcd_puts("Msg Memory Clear");

wait(2);
lcd_clrscr();
wait(1);;
DDRB=0b00010000; //declare PD4 as a output pin connected to the buzzer

int i;
unsigned char number[12];
USARTInit(77); //Baud rate initialize
lcd_init(LCD_DISP_ON); //LCD initialization
DDRB=0xFF;
while(1) //infinite loop
{
while(1)
{
data=USARTReadChar(); // waiting to receive new data
for(i=0;i<12;i++)
{
number[i]=USARTReadChar();
}
number[12]='\0';
if((strcmp(number,stored_data)==0))
{
lcd_clrscr();
lcd_gotoxy(0,0);
lcd_puts("Matched");
PORTB=0xFF;
lcd_gotoxy(0,1);
lcd_puts(data);
USARTWriteChar('A'); // Then print AC ON on LCD & sending the AT

command

USARTWriteChar('T'); // to modem to send a msg. to a number
USARTWriteChar('+');
USARTWriteChar('C');
USARTWriteChar('M'); // AT+CMGS=Mobile no.<carrige return>to

which return msg is to be send
USARTWriteChar('G');

USARTWriteChar('S');
USARTWriteChar('=');
USARTWriteChar('"');
USARTWriteChar('+');
USARTWriteChar('9');
USARTWriteChar('1');
USARTWriteChar('9');
USARTWriteChar('7');
USARTWriteChar('1');
USARTWriteChar('7');
USARTWriteChar('9');
USARTWriteChar('8');
USARTWriteChar('8');
USARTWriteChar('5');
USARTWriteChar('2');
USARTWriteChar('0');
USARTWriteChar('"');
USARTWriteChar('\n\r');

wait(5);
USARTWriteChar('Y');
USARTWriteChar('o');
USARTWriteChar('u'); // Msg. Text to be sent by the modem

USARTWriteChar('r');

USARTWriteChar(' ');
USARTWriteChar('F');
USARTWriteChar('a');
USARTWriteChar('m');
USARTWriteChar('i');
USARTWriteChar('l');
USARTWriteChar('y');
USARTWriteChar(' ');
USARTWriteChar('m'); // Msg. Text to be sent by the modem

USARTWriteChar('e');

USARTWriteChar('m');
USARTWriteChar('b');
USARTWriteChar('e');

USARTWriteChar('r');
USARTWriteChar(' ');
USARTWriteChar('i');
USARTWriteChar('s');
USARTWriteChar(' ');
USARTWriteChar('E');
USARTWriteChar('n');

USARTWriteChar('t');
USARTWriteChar('e');
USARTWriteChar('r');
USARTWriteChar('e');
USARTWriteChar('d');
USARTWriteChar(26); // ASCII for Ctrl+Z

USARTWriteChar('\n\r');

}

else
{
lcd_clrscr();
lcd_gotoxy(0,0);
lcd_puts("Not Matched");
PORTB=0x00;
lcd_gotoxy(0,1);
lcd_puts(data);
USARTWriteChar('A'); // Then print AC ON on LCD & sending the AT

command

USARTWriteChar('T'); // to modem to send a msg. to a number
USARTWriteChar('+');
USARTWriteChar('C');
USARTWriteChar('M'); // AT+CMGS=Mobile no.<carrige return>to

which return msg is to be send
USARTWriteChar('G');

USARTWriteChar('S');
USARTWriteChar('=');
USARTWriteChar('"');
USARTWriteChar('+');
USARTWriteChar('9');
USARTWriteChar('1');
USARTWriteChar('9');
USARTWriteChar('7');
USARTWriteChar('1');
USARTWriteChar('7');
USARTWriteChar('9');
USARTWriteChar('8');
USARTWriteChar('8');
USARTWriteChar('5');
USARTWriteChar('2');
USARTWriteChar('0');
USARTWriteChar('"');
USARTWriteChar('\n\r');

wait(5);

USARTWriteChar('S');
USARTWriteChar('o');
USARTWriteChar('m'); // Msg. Text to be sent by the modem

USARTWriteChar('e');

USARTWriteChar(' ');
USARTWriteChar('O');
USARTWriteChar('n');
USARTWriteChar('e');
USARTWriteChar(' ');
USARTWriteChar('i');
USARTWriteChar('s');
USARTWriteChar(' ');
USARTWriteChar('t'); // Msg. Text to be sent by the modem

USARTWriteChar('r');

USARTWriteChar('y');
USARTWriteChar(' ');
USARTWriteChar('t');
USARTWriteChar('o');
USARTWriteChar(' ');
USARTWriteChar('E');
USARTWriteChar('n');
USARTWriteChar('t');
USARTWriteChar('e');
USARTWriteChar('r');
USARTWriteChar(' ');
USARTWriteChar('i');
USARTWriteChar('n');
USARTWriteChar(' ');
USARTWriteChar('y');

USARTWriteChar('o');
USARTWriteChar('u');
USARTWriteChar('r');
USARTWriteChar(' ');
USARTWriteChar('h');
USARTWriteChar('o');
USARTWriteChar('u');
USARTWriteChar('s');
USARTWriteChar('e');
USARTWriteChar(26); // ASCII for Ctrl+Z

USARTWriteChar('\n\r');

wait(3);
}
wait(2);

USARTWriteChar('A');
USARTWriteChar('T');
USARTWriteChar('+'); // Sending AT Command AT+CMGD=1 to the

modem

USARTWriteChar('C');
USARTWriteChar('M'); // to delete inbox msg. at position no.1
USARTWriteChar('G');
USARTWriteChar('D');
USARTWriteChar('=');

USARTWriteChar('1');
USARTWriteChar('\n\r');
wait(2);
lcd_clrscr(); //celar screen
lcd_puts("Msg Deleted");
wait(2);
lcd_clrscr();
wait(2);;
}
}

}
