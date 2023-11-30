#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


void LCD_init(void)
{
	// Intialize LCD pins As OutPut Pins
	DIO_setPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);

	_delay_ms(35);
	DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	DIO_setPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	private_writeHalfPort(0b0010);
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
	
	// Function Set command 2*16 LCD , 4 Bit Mode
	LCD_sendCmnd(0b00101000);
	_delay_us(45);
	
	// Display on off Control (DisplayOn, Cursor on, Blink on)
	LCD_sendCmnd(0b00001111);
	_delay_us(45);
	
	// Clear Display
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);
	
	LCD_sendCmnd(0b00000110);
}

void LCD_sendCmnd(u8 Cmnd)
{
	// set Rs pin = 0 (write command)
	DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	
	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	
	// Write The Most 4 bits Of command on Data Pins
	private_writeHalfPort(Cmnd>>4);
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
	
	// Write The Least 4 bits Of command on Data Pins
	private_writeHalfPort(Cmnd);
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
}
void LCD_sendChar(u8 data)
{
	// set Rs pin = 1 (write data)
	DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	
	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	
	// Write The Most 4 bits Of data on Data Pins
	private_writeHalfPort(data>>4);
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
	
	// Write The Least 4 bits Of data on Data Pins
	private_writeHalfPort(data);
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_EN_PORT, LCD_EN_PIN, DIO_PIN_LOW);
}



static void private_writeHalfPort(u8 value)
{
	if(GET_BIT(value,0) == 0)
	{
		DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_LOW);
	}
	else
	{
		DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_HIGH);
	}
	
	if(GET_BIT(value,1) == 0)
	{
		DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_LOW);
	}
	else
	{
		DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_HIGH);
	}
	
	if(GET_BIT(value,2) == 0)
	{
		DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_LOW);
	}
	else
	{
		DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_HIGH);
	}
	
	if(GET_BIT(value,3) == 0)
	{
		DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_LOW);
	}
	else
	{
		DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_HIGH);
	}
}


void LCD_SendString (u8 *String_Data)
{
	while( (*String_Data)!= '\0'  )
	{
		LCD_sendChar(*String_Data);
		String_Data++ ;
	}
}

void LCD_SendIntegarNumber(u16 IntegarNumber) 
{
	u16 NumberString[16];
	snprintf(NumberString, 17, "%d", IntegarNumber);
	LCD_SendString(NumberString);
}


void LCD_SendRealNumber(f64 Number)
{
	u8 str [16];
	u8 *tmpsign = (Number < 0)? "-" : "";
	f32 tmpval = (Number < 0)? -Number : Number;
	u16 tmpint1 = (u16)tmpval;
	f32 tmpfrac = tmpval - (float)tmpint1;
	u16 tmpint2 = tmpfrac * 10000;
	sprintf(str,"%s%d.%04d", tmpsign, tmpint1, tmpint2);
	LCD_SendString(str);
}

