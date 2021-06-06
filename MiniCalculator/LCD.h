
#ifndef LCD_H_
#define LCD_H_
# define F_CPU 8000000
# include <util/delay.h>
#include "DIO_Interface.h"

/***************************************************/

#define  RS PINA1
#define  EN PINA2
#define  LCD_PORT PA

#define  LCD_PIN4  PINA3#define  LCD_PIN5  PINA4#define  LCD_PIN6  PINA5#define  LCD_PIN7  PINA6

#define LCD8_BITMODE 0#define LCD4_BITMODE 1#define LCD_MODE LCD4_BITMODE

 
/*****************************************************/

void LCD_Init (void);
void LCD_WriteChar(u8 ch);
void LCD_WriteNumber(s64 num);
void LCD_WriteString(u8*str);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_WriteNumber_4D(u16 num);
void LCD_WriteFloat(f32 Copy_f32Number);
void LCD_Clear(void);
void LCD_ClearCells(u8 line,u8 cell,u8 num);
void LCD_SetCursor(u8 line,u8 cell);
void LCD_ShiftCursorLeft(void);
void LCD_SetCursor1(u8 line, u8 cell);
void LCD_CursorWriteString(u8 line,u8 cell,u8*str);

void Create_Character(u8*arr_figure,u8 place);
void dead_man(void);
void playing_man(u8 updown,u8 r_l);




	
#endif /* LCD_H_ */