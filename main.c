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


//---------------------------- MAIN CODE ---------------------------------------

int main() {


    PinsInit();
    Lcd_Init();

    StopMotor();
    configurarDerecha();
    configurarIzquierda();

    while (1) {

        keypress = KeyPadGetKey();

        //Si se presiona una tecla
        if (keypress != keyPadMatrix[ 0x10 ]) {

            switch (keypress) {
                case 'A':
                    configurarDerecha();
                    break;
                case'B':
                    configurarIzquierda();
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

int configurarDerecha() {

    buffer = 0;
    StopMotor();

    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Config-derecha: ");

    while (1) {

        keypress = KeyPadGetKey();
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

int configurarIzquierda() {

    buffer = 0;
    StopMotor();

    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("Config-izquierda: ");

    while (1) {

        keypress = KeyPadGetKey();
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

    if (MotorHorario) {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Dir: Horario");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Integer(Grados * CteVueltas);
        Lcd_Write_String(" Cm de: ");
        Lcd_Write_Integer(CmHorario);
    } else {
        Lcd_Clear();
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("Dir: AntiHorario");
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_Integer(Grados * CteVueltas);
        Lcd_Write_String(" Cm de: ");
        Lcd_Write_Integer(CmAntiHorario);
    }
    return 0;
}


