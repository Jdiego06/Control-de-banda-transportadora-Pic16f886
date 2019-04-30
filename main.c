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
//#include <stdlib.h>
//#include <stdio.h>
//Variables del programa

char keypress = '0';
int key2 = '0';

int buffer = 0;

int CmDerecha = 0;
int CmIzquierda = 0;

//char Data[10];

int main() {
    unsigned int a;
    ANSELH = ANSEL = 0;
    //TRISC=  0x00;
    TRISB = 0x00;


    UART_Init(9600);
    nRBPU = 0;
    Lcd_Init();
    KeyPadInit();



    while (1) {


        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);




        //UART_Write_Text(myStg);

        //UART_Write(x);

        keypress = KeyPadGetKey(); //Si se preciono una tecla
        if (keypress != keyPadMatrix[ 0x10 ]) {


            switch (keypress) {
                case 'A':
                    UART_Write_Text("Va a configurar derecha ");

                    configurarDerecha();
                    break;
                case'B':
                    UART_Write_Text("Va a configurar I ");
                    Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Config-derecha: ");
                    configurarIzquierda();
                    break;
                case'C':
                    StopMotor();
                    break;
                case'D':
                    RunMotor();

                    break;
            }
            __delay_ms(10);
        }
    }
    return 0;
}

configurarDerecha() {

    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Config-derecha: ");

    buffer = 0;
    StopMotor();

    Lcd_Set_Cursor(2, 1);
    while (1) {

        keypress = KeyPadGetKey(); //Si se preciono una tecla
        if (keypress != keyPadMatrix[ 0x10 ]) {
            key2 = keypress;
            switch (key2) {

                case 'A':
                    break;
                case 'B':
                    break;
                case 'C':
                    break;
                case 'D':
                    CmDerecha = buffer;
                    RunMotor();
                    return 0;
                    break;
                case '*':
                    break;
                case '#':
                    break;
                default:
                    buffer = (10 * buffer + key2);
                    buffer -= 48;
                    Lcd_Set_Cursor(2, 1);
                    Lcd_Write_Integer(buffer);
            }
        }
        __delay_ms(10);
    }
}

configurarIzquierda() {

    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Config-izquierda: ");

    buffer = 0;
    StopMotor();

    Lcd_Set_Cursor(2, 1);
    while (1) {

        keypress = KeyPadGetKey(); //Si se preciono una tecla
        if (keypress != keyPadMatrix[ 0x10 ]) {
            key2 = keypress;
            switch (key2) {

                case 'A':
                    break;
                case 'B':
                    break;
                case 'C':
                    break;
                case 'D':
                    CmIzquierda = buffer;
                    RunMotor();
                    return 0;
                    break;
                case '*':
                    break;
                case '#':
                    break;
                default:
                    buffer = (10 * buffer + key2);
                    buffer -= 48;
                    Lcd_Set_Cursor(2, 1);
                    Lcd_Write_Integer(buffer);

            }
        }
        __delay_ms(10);
    }
}

RunMotor() {
    UART_Write_Text("Run Motor");
    int y = 0;
    for (y = 0; y < 300; y++) {
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_Integer(y);
        __delay_ms(1000);
        UART_Write('W');
    }
    return 0;

}

StopMotor() {
    UART_Write_Text("Stop Motor");
    return 0;
}