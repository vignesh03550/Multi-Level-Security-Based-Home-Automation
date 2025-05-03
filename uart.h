 #include<LPC21XX.h>
#include <stdio.h>
void pinconfig(void);
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned  char UART0_RX(void);
void UART_STR(unsigned char *);

void pinconfig(void)
{
	PINSEL0|=0X05;
}
void UART0_CONFIG(void)
{
 	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
void UART0_TX(unsigned char d)
{
	U0THR=d;
	while(((U0LSR>>5)&1)==0); 	
}
unsigned  char UART0_RX(void)
{
 	while((U0LSR&1)==0);
	return U0RBR;
}
void UART0_STR(unsigned char *s)
{
	while(*s)
	UART0_TX(*s++);	
}
void UART0_INTEGER (int num)
{
    char buf[10];
	sprintf(buf,"%d",num);
	UART0_STR(buf);
}
