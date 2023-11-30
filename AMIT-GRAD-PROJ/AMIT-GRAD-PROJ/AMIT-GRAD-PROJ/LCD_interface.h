/*
 * LCD_interface.h
 *
 * Created: 9/10/2023 2:56:20 PM
 *  Author: Baba
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_init(void);
void LCD_sendCmnd(u8 cmnd);
void LCD_sendChar(u8 data);
void LCD_SendIntegarNumber(u16 IntegarNumber) ;
void LCD_SendString (u8 *String_Data);
void LCD_SendRealNumber(f64 Number);


#endif /* LCD_INTERFACE_H_ */