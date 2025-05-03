#include<LPC21XX.H>
#include"delay.h"
#define lcd_d 0Xf<<20
#define rs 1<<17
#define rw 1<<18
#define e 1<<19

typedef unsigned char u8;
void lcd_command(unsigned char);
void lcd_data (unsigned char);
void lcd_config(void);
void lcd_string(unsigned char*);
void lcd_integer(int);
void lcd_float(float);

void lcd_config(void)
{
//PINSEL1=0X00000000;
IODIR1=lcd_d|rs|rw|e;
IOCLR1=rw;
lcd_command(0x01);
lcd_command(0x02);
lcd_command(0x0c);
lcd_command(0x28);
lcd_command(0x80);
}

void lcd_command(u8 cmd)
{
IOCLR1=lcd_d;
IOSET1=(cmd&0xf0)<<16;
IOCLR1=rs;
IOSET1=e;
delay_ms(2);
IOCLR1=e;

IOCLR1=lcd_d;
IOSET1=(cmd&0x0f)<<20;
IOCLR1=rs;
IOSET1=e;
delay_ms(2);
IOCLR1=e;
}

void lcd_data(u8 data)
{
IOCLR1=lcd_d;
IOSET1=(data&0xf0)<<16;
IOSET1=rs;
IOSET1=e;
delay_ms(2);
IOCLR1=e;

IOCLR1=lcd_d;
IOSET1=(data&0x0f)<<20;
IOSET1=rs;
IOSET1=e;
delay_ms(2);
IOCLR1=e;
}

void lcd_string(u8 *s)
/*{
while(*s)
lcd_data(*s++);
}*/
{
 char pos=0;
 while(*s)
 {
 lcd_data(*s++);
 pos++;
 if(pos==16)
 lcd_command(0Xc0);
 }
}
void lcd_integer(int n)  
{
u8 arr[5];
signed char i=0;
if(n==0)
lcd_data('0');
else
  {
  if(n<0)
  {
   lcd_data('-');
   n=-n;
  }
 		while(n>0)
		{
		arr[i++]=n%10;
		n=n/10;
		}
		for(--i;i>=0;i--)
		lcd_data(arr[i]+48);
		}
}

void lcd_float(float f)
{
int x=f;
lcd_integer(x);
lcd_data('.');
f=f-x*10;
lcd_integer(f);
}  
