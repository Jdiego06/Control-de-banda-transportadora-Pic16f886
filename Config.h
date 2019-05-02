#define _XTAL_FREQ 4000000
#include <xc.h>

//Constamte del encoder Se calcula así: DiametroRodillo/PulsosVueltaEncoder 
//Ej: 35Cm/360Pulses = 0.097
#define CteVueltas 0.097


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


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

void PinsInit() {
    //All Pins Digitals
    ANSELH = ANSEL = 0;

    //for Lcd
    TRISB = 0x01;

    //Port C as Output
    TRISC = 0x00;
    PORTC = 0x00;

    //For Keypad
    TRISA = 0xf0;
    PORTA = 0x00;
}



