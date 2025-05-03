#include<LPC21XX.H>
char* gsm_OTP(void)
{
    int r=1000;
	char OTP[5];
	pinconfig();
	UART0_CONFIG();
	for(;;r++)
	{							     
	 r^=19;
	 if((r>999)&&(r<=9999))
	 {

	 UART0_STR("AT\r\n");
	 delay_ms(1000);
	 UART0_STR("AT+CMGF=1\r\n");
	 delay_ms(1000);
	 UART0_STR("AT+CMGS=\"+917397541107\"\r\n");
	 delay_ms(1000);
	 sprintf(OTP,"%d",r);
	 UART0_STR(OTP);
	 UART0_STR("\r\n");
	 UART0_TX(26);
	 delay_ms(1000);
	 }
	 return OTP;
	}	
}
                      