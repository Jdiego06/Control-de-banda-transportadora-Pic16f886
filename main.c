#define _XTAL_FREQ 8000000

#define RS RB2
#define EN RB3
#define D4 RB4
#define D5 RB5
#define D6 RB6
#define D7 RB7

// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

#include <xc.h>
#include "lcd.h"
#include "uart.h"
#include "KeyPad.h"

int main() {
    unsigned int a;
    ANSELH = ANSEL = 0;
    //TRISC=  0x00;
    TRISB = 0x00;

    char keypress = '0';

    UART_Init(9600);
    nRBPU = 0;
    Lcd_Init();
    KeyPadInit();


    while (1) {




        keypress = KeyPadGetKey();
        if (keypress != keyPadMatrix[ 0x10 ]) {
            UART_Write(keypress);
            Lcd_Clear();
            Lcd_Set_Cursor(1, 1);
            Lcd_Write_String("Hola");
            UART_Write_Text("Hola");
        } else {
            UART_Write('-');
        }

        __delay_ms(10);


    }
    return 0;
}