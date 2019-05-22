/*---------------------------------------------------------------------------------------
 * Description:
 * 				This code contains a set of functions that allow
 *              you to configure the system, as well as control 
 *              the motors, and read the pulses of the encoder
 * --------------------------------------------------------------------------------------*/

#include "Controls.h"

int Grados;
int key2 = '0';
int buffer = 0;
int CmHorario = 0;
int CmAntiHorario = 0;
int cm = 0;
int lastCm = 0;

/*---------------------------------------------------------------------------------------
 *		Disable the analog ports and configure the ports as outputs or inputs.
 * --------------------------------------------------------------------------------------*/
void ConfigInit() {

    //Oscillator
    OSCCONbits.IRCF = 0x7; //8MHz Clock
    OSCCONbits.SCS = 0;
    OSCTUNE = 0x00;

    //All Pins Digitals
    ANSELH = ANSEL = 0;

    //for Lcd
    TRISB = 0x01;

    //Port C as Output
    TRISC = 0x00;
    PORTC = 0x00;

    //For Keypad
    TRISA = 0xE8;
    PORTA = 0x00;

}

/*---------------------------------------------------------------------------------------
 *                                      Start the engine
 * --------------------------------------------------------------------------------------*/
int RunMotor() {
    if (CmAntiHorario != 0 && CmHorario != 0) {
        MotorHorario = 1;
        MotorAntiHorario = 0;
    }
    return 0;
}

/*---------------------------------------------------------------------------------------
 *                                      Stop the engine
 * --------------------------------------------------------------------------------------*/
int StopMotor() {
    MotorAntiHorario = 0;
    MotorHorario = 0;
    return 0;
}

/*---------------------------------------------------------------------------------------
 *             This function configures the amount of displacement 
 *             of the motor counterclockwise, by means of the keyboard input.
 * --------------------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------------------
 *             This function configures the amount of displacement 
 *             of the motor clockwise, by means of the keyboard input.
 * --------------------------------------------------------------------------------------*/
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

/*---------------------------------------------------------------------------------------
 *			This function checks if the current displacement is equal to the programmed
 *          one, and if so, reverses the motor rotation
 * --------------------------------------------------------------------------------------*/
int VerificarInversionGiro() {
    if (MotorHorario && (Grados * CteVueltas >= CmHorario)) {
        Grados = 0;
        MotorHorario = !MotorHorario;
        __delay_ms(1000);
        MotorAntiHorario = !MotorAntiHorario;
        lastCm = 0;
    } else if (MotorAntiHorario && Grados * CteVueltas >= CmAntiHorario) {
        Grados = 0;
        MotorAntiHorario = !MotorAntiHorario;
        __delay_ms(1000);
        MotorHorario = !MotorHorario;
        lastCm = 0;
    }
    return 0;
}

/*---------------------------------------------------------------------------------------
 *			This function takes the current displacement count, and prints on the LCD,
 *          the direction of rotation, and the distance in cm
 * --------------------------------------------------------------------------------------*/
int Encoder() {
    LastState = true;
    Grados++;
    VerificarInversionGiro();
    RC2 = !RC2;
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
