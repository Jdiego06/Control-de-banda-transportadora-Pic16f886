#include "Config.h"
#include <xc.h>
#include "lcd.h"
#include "KeyPad.h"
#include <stdbool.h>


// ------------------ Variables Del Programa --------------------------

int Grados = 0;
int key2 = '0';
int buffer = 0;
int CmHorario = 0;
int CmAntiHorario = 0;
bool LastState = false;
char keypress = '0';
int cm = 0;


//---------------------------- MAIN CODE ---------------------------------------

int main() {


    PinsInit();
    Lcd_Init();

    StopMotor();
    configurarHorario();
    configurarAntiHorario();

    while (1) {

        keypress = KeyPadGetKey();

        //Si se presiona una tecla
        if (keypress != keyPadMatrix[ 0x10 ]) {

            switch (keypress) {
                case 'A':
                    configurarHorario();
                    break;
                case'B':
                    configurarAntiHorario();
                    break;
                case'C':
                    StopMotor();
                    break;
                case'D':
                    RunMotor();
                    break;
            }
        }

        // Si se presenta un pulso del encoder
        if (pinEncoder == 1 && LastState == false) {
            Encoder();
        } else if (pinEncoder == 0) {
            LastState = false;
        }
        __delay_ms(1);
    }
    return 0;
}


//----------------------------------- SUBRUTINAS -------------------------------

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
        __delay_ms(1);
    }
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

int VerificarInversionGiro() {
    if (MotorHorario && (Grados * CteVueltas >= CmHorario)) {
        Grados = 0;
        MotorHorario = !MotorHorario;
        MotorAntiHorario = !MotorAntiHorario;
    } else if (MotorAntiHorario && Grados * CteVueltas >= CmAntiHorario) {
        Grados = 0;
        MotorHorario = !MotorHorario;
        MotorAntiHorario = !MotorAntiHorario;
    }
    return 0;
}

int Encoder() {
    LastState = true;
    Grados++;
    VerificarInversionGiro();

    cm = Grados * CteVueltas;

    if (MotorHorario && (Grados * CteVueltas != cm)) {
        cm = Grados * CteVueltas;
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Dir: Adelante");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Integer(cm);
        Lcd_Write_String(" Cm de: ");
        Lcd_Write_Integer(CmHorario);
    } else if (MotorAntiHorario && (Grados * CteVueltas != cm)) {
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


