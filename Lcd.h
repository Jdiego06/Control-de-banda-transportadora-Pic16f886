#ifndef LCD_H
#define  LCD_H

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <xc.h>


/*    Lcd Pins    */
#define RS RB2
#define EN RB3
#define D4 RB7
#define D5 RB4
#define D6 RB6
#define D7 RB5

void Lcd_Port(char a);
void Lcd_Clear(void);
void Lcd_Cmd(char a);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void) ;
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Write_Integer(int a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);

#endif