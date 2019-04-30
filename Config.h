#define _XTAL_FREQ 8000000
#include <xc.h>

//Constantes del sistema mecánico
#define Diametro 35
#define PulsosVuelta 360


//KeyPad Pins
#define row1 RA0
#define row2 RA1
#define row3 RA2
#define row4 RA3
#define col1 RA4
#define col2 RA5
#define col3 RA6
#define col4 RA7 


//Lcd Pins
#define RS RB2
#define EN RB3
#define D4 RB4
#define D5 RB5
#define D6 RB6
#define D7 RB7


//Program Definitions
#define pinEncoder RB0
#define MotorHorario RC0
#define MotorAntiHorario RC1



//  Se calcula así: DiametroRodilloBanda/pulsosPorVuelta
#define CteVueltas (Diametro/PulsosVuelta)


// Pragma Config
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)

void PinsInit() {
    //All Pins Digitals
    ANSELH = ANSEL = 0; 

    //for Lcd
    TRISB = 0x01;
    
    //Port C as Output
    TRISC = 0x00;
    
    //For Keypad
    TRISA = 0xf0; 
    PORTA = 0x00;
}



