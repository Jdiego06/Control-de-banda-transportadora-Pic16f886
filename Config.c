#include "Config.h"
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "KeyPad.h"
#include "lcd.h"

void ConfigInit() {

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


    nRBPU = 0;
    UART_Init(9600);
    Lcd_Init();

}

int RunMotor() {
    if (CmAntiHorario != 0 && CmHorario != 0) {
        MotorHorario = 1;
        MotorAntiHorario = 0;
    }
    return 0;
}

int StopMotor() {
    MotorAntiHorario = 0;
    MotorHorario = 0;
    return 0;
}

int configurarAntiHorario() {

    buffer = 0;
    StopMotor();

    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Atras: ");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("0 Cm");

    while (1) {

        keypress = KeyPadGetKey();
        if (keypress != keyPadMatrix[ 0x10 ]) {
            key2 = keypress;
            switch (key2) {
                case 'A':
                    break;
                case 'B':
                    buffer = 0;
                    Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Atras: ");
                    Lcd_Set_Cursor(2, 1);
                    Lcd_Write_String("0 Cm");
                    break;
                case 'C':
                    break;
                case 'D':
                    Grados = 0;
                    CmAntiHorario = buffer;
                    RunMotor();
                    if (CmAntiHorario != 0) {
                        return 0;
                    }
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
                    Lcd_Write_String(" Cm");
            }
        }
        __delay_ms(1);
    }
}

int configurarHorario() {

    buffer = 0;
    StopMotor();

    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Adelante: ");
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("0 Cm");

    while (1) {

        keypress = KeyPadGetKey();
        if (keypress != keyPadMatrix[ 0x10 ]) {
            key2 = keypress;
            switch (key2) {

                case 'A':
                    buffer = 0;
                    Lcd_Clear();
                    Lcd_Set_Cursor(1, 1);
                    Lcd_Write_String("Adelante: ");
                    Lcd_Set_Cursor(2, 1);
                    Lcd_Write_String("0 Cm");
                    break;
                case 'B':
                    break;
                case 'C':
                    break;
                case 'D':
                    Grados = 0;
                    CmHorario = buffer;
                    RunMotor();
                    if (CmHorario != 0) {
                        return 0;
                    }
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
                    Lcd_Write_String(" Cm");
            }
        }
        //__delay_ms(1);
    }
}

int VerificarInversionGiro() {
    if (MotorHorario && (Grados * CteVueltas >= CmHorario)) {
        Grados = 0;
        MotorHorario = !MotorHorario;
        MotorAntiHorario = !MotorAntiHorario;
        lastCm = 0;
    } else if (MotorAntiHorario && Grados * CteVueltas >= CmAntiHorario) {
        Grados = 0;
        MotorHorario = !MotorHorario;
        MotorAntiHorario = !MotorAntiHorario;
        lastCm = 0;
    }
    return 0;
}

int Encoder() {
    LastState = true;
    Grados++;
    VerificarInversionGiro();

    cm = Grados * CteVueltas;

    if (MotorHorario && (cm > lastCm)) {
        lastCm = cm + 0.9;
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Dir: Adelante");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Integer(cm);
        Lcd_Write_String(" Cm de: ");
        Lcd_Write_Integer(CmHorario);
    } else if (MotorAntiHorario && (cm > lastCm)) {
        lastCm = cm + 0.9;
        cm = Grados * CteVueltas;
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Dir: Atras");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Integer(Grados * CteVueltas);
        Lcd_Write_String(" Cm de: ");
        Lcd_Write_Integer(CmAntiHorario);
    }
    return 0;
}
