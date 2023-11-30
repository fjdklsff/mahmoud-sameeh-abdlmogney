#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "DIO_interface.h"
#include "LCD_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

int main ( )
{
	unsigned int a,b,c,high,period;
	char frequency[14],duty_cy[7],PER[10];
	
	LCD_init();
	PORTD = 0xFF;
	
	while(1)
	{
		TCCR1A = 0;
		TCNT1=0;
		TIFR = (1<<ICF1);
		
		TCCR1B = 0x41;
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;
		TIFR = (1<<ICF1);
		
		TCCR1B = 0x01;
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;
		TIFR = (1<<ICF1);
		
		TCCR1B = 0x41;
		while ((TIFR&(1<<ICF1)) == 0);
		c = ICR1;
		TIFR = (1<<ICF1);
		
		TCCR1B = 0;
		
		if(a<b && b<c)
		
		{
			high=b-a;
			period=c-a;
			
			u32 freq= F_CPU/period;
			freq=freq/1000;
			
			
			f32 duty_cycle =((f32) high /(f32)period)*100;
			ltoa(freq,frequency,10);
			
			char fr[100]="Freq: ";
			char hz[5]=" KHZ";
			strcat(fr,frequency);
			strcat(fr,hz);
			
			itoa((int)duty_cycle,duty_cy,10);
			char du[100]="Duty: ";
			char perc[5]=" %";
			strcat(du,duty_cy);
			strcat(du,perc);
			
			f32 time =(1/(f32)freq);
			LCD_SendString(fr);
			LCD_sendChar(' ');
			LCD_SendString(du);
			LCD_sendChar(' ');
			LCD_SendString("Time: ");
			LCD_SendRealNumber(time);
			LCD_SendString("ms");
			char a [40];
			char arrow[10];
			
			strcat(arrow,"<-");
			
			for (u32 i = 0;i<2;i++)
			{
				for (u32 j=0;j<(duty_cycle/10);j++)
				{
					strcat(a,"-");
				}
				for (u32 k=0;k<(10-(duty_cycle/10));k++)
				{
					strcat(a,"_");
				}
			}
			
			LCD_sendCmnd(0xC0);
			LCD_SendString(a);
			
			
			
		}
		
		else
		{
			LCD_sendCmnd(0x01);
			LCD_SendString("OUT OF RANGE!!");
			
		}
		
		_delay_ms(100000);
		LCD_sendCmnd(0x01);
	}

}