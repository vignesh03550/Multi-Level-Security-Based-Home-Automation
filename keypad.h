 #include<LPC21XX.H>
#include"lcd.h"
//DEFINE COLUMNS
#define c0 (IOPIN0&(1<<16))
#define c1 (IOPIN0&(1<<17))
#define c2 (IOPIN0&(1<<18))
#define c3 (IOPIN0&(1<<19))
//DEFINE ROWS
#define r0 1<<20
#define r1 1<<21
#define r2 1<<22
#define r3 1<<23
typedef unsigned char u8;
//DEFINE 2D ARRAY TO ASSIGN KEYVALUES
unsigned int key_lut[4][4]={{1,2,3,4},{5,6,7,8},{9,0,11,12},{13,14,15,16}};
unsigned int keyscan(void)
{
 	u8 row_val,col_val;
	PINSEL0|=0X00000000;
	IODIR0|=r0|r1|r2|r3;

	while(1)
	{
	IOCLR0|=r0|r1|r2|r3;
	IOSET0|=c0|c1|c2|c3;
	
	while((c0&&c1&&c2&&c3)==1);		 //wait for switch press
	//TO CHECK ROW VALUES
	IOCLR0|=r0;
	IOSET0|=r1|r2|r3;
	if((c0&&c1&&c2&&c3)==0)
	{
	row_val=0;
	break;
	}
	IOCLR0=r1;
	IOSET0=r0|r2|r3;
	if((c0&&c1&&c2&&c3)==0)
	{
	row_val=1;
	break;
	}
	IOCLR0=r2;
	IOSET0=r0|r1|r3;
	if((c0&&c1&&c2&&c3)==0)
	{
	row_val=2;
	break;
	}
	IOCLR0=r3;
	IOSET0=r0|r1|r2;
	if((c0&&c1&&c2&&c3)==0)
	{
	row_val=3;
	break;
	}
   }
   //CHECK COLUMN VALUES
   if(c0==0)
   col_val=0;
   else if(c1==0)
   col_val=1;
   else if(c2==0)
   col_val=2;
   else 
   col_val=3;
   delay_ms(250);//TO AVIOD SWITCH BOUNCING

   	while((c0&&c1&&c2&&c3)==0);	//wait for key release

	return key_lut[row_val][col_val];
}
	