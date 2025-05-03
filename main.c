  #include <LPC21XX.H>
#include<string.h>
#include "uart.h"
#include "i2chead.H"
#include "keypad.h"
#include "motor.h"
//#include "gsm.h"
#define sw 14
#define length 4
#define I2C_EEPROM_SA 0x50 //7Bit Slave Addr

u8 p[9] __attribute__((at(0x40000040)))="";
 int main()
 {
 int i,count=0,OTP_count=0,r;
 char key,keyy,a[5],b[5],OTP[5];
 lcd_config();
 init_i2c();
 pinconfig();
 UART0_CONFIG();
 motor_init();

 i2c_eeprom_page_write(I2C_EEPROM_SA,0x00,"9525",4); 
 i2c_eeprom_seq_read(I2C_EEPROM_SA,0x00,p,4);
 delay_ms(100);
 lcd_command(0x01);
 lcd_command(0x80);
 lcd_string("MULTILEVEL BASED SECURITY SYSTEM");
 
 while(1)
 {
  if(((IOPIN0>>sw)&1)==0)
   {
   label:
   lcd_command(0x01);
   lcd_command(0x80);
   lcd_string("Enter Password");
   lcd_command(0xc0);
   for(i=0;i<length;i++)
   {
	key=keyscan()+48;
	a[i]=key;
	lcd_command(0xc0+i);
	lcd_data('*');
   }
   a[i]='\0';
   r=1000;
   abc:
   if(strcmp(p,a)==0)	  //main if part
   {
   lcd_command(0x01);
   lcd_command(0x80);
   lcd_string("OTP Sending...");

   /*strcpy(otp,gsm_OTP());
   char* gsm_OTP(void)
   int r=1000;
	char OTP[5];
	pinconfig();
	UART0_CONFIG();*/
	for(;;r++)
	{							     
	 r^=19;
	 if((r>999)&&(r<=9999))
	 {

	 UART0_STR("AT\r\n");
	 delay_ms(1000);
	 UART0_STR("AT+CMGF=1\r\n");
	 delay_ms(1000);
	 UART0_STR("AT+CMGS=\"+918870834233\"\r\n");
	 delay_ms(1000);
	 sprintf(OTP,"%d",r);
	 UART0_STR(OTP);
	 UART0_STR("\r\n");
	 UART0_TX(26);
	 delay_ms(1000);
	 break;
	 }
	 //return OTP;
	}	

   //strcpy(otp,gsm_OTP());                  
   lcd_command(0x01);
   lcd_command(0x80);
   lcd_string("Enter OTP");
   lcd_command(0xc0);
   for(i=0;i<length;i++)
    {
	 keyy=keyscan()+48;
	 b[i]=keyy;
	 lcd_command(0xc0+i);
	 lcd_data('#');
    }
     b[i]='\0';

   	 if(strcmp(OTP,b)==0)			  //password comparition   //if part
	  {
	   lcd_command(0x01);
       lcd_command(0x80);
       lcd_string("OTP Mathched");
	   delay_ms(500);
	   lcd_command(0x01);
       lcd_command(0x80);
       lcd_string("Door Opened");
	   motor_forward();
	   delay_s(5);
	   motor_off();
	   lcd_command(0x01);
       lcd_command(0x80);
       lcd_string("Door Closed");
	   motor_backward();
	   delay_s(5);
	   motor_off();


	  }
	  else
	  {
	   lcd_command(0x01);
       lcd_command(0x80);
       lcd_string("OTP Mismathched");
	   ++OTP_count;
	    if(OTP_count<3)
	    goto abc;
	    else
	    {
	    UART0_STR("AT\r\n");
	    delay_ms(1000);
	    UART0_STR("AT+CMGF=1\r\n");
	    delay_ms(1000);
	    UART0_STR("AT+CMGS=\"+918870834233\"\r\n");										//9061319953-A
	    delay_ms(1000);
	    UART0_STR("Some One Access Your Door\r\n");
	    delay_ms(1000);
	    UART0_TX(26);
	    delay_ms(1000);
        } //else
	  }

    }


   else				   	  //main else part
   {
    ++count;
	lcd_command(0x01);
    lcd_command(0x80);
    lcd_string("wrong Password");
	delay_ms(500);

	if(count<3)
	goto label;
	else
	{
	 UART0_STR("AT\r\n");
	 delay_ms(1000);
	 UART0_STR("AT+CMGF=1\r\n");
	 delay_ms(1000);
	 UART0_STR("AT+CMGS=\"+918870834233\"\r\n");
	 delay_ms(1000);
	 UART0_STR("Some One Access Your Door\r\n");
	 delay_ms(1000);
	 UART0_TX(26);
	 delay_ms(1000);
    } //else

   } //else
   }//if
 }//while
 
}//main
