 /*---------------------------------------------------------------------------------------
 * Description:
 * 				This is the main code, checks the pulses of the encoder, 
 *              or inputs by keypad and call the other functions
 * --------------------------------------------------------------------------------------*/

#include "main.h"

char keypress='0';
bool LastState=false;

int main() {   
    ConfigInit(); 
    Lcd_Init();
    StopMotor();
    configurarHorario();
    configurarAntiHorario();

    while (1) {
        
        keypress = KeyPadGetKey();

        //If key is press
        if (keypress != 0xFF) {

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


        if (pinEncoder == 1 && LastState == false) {
            Encoder();
        } else if (pinEncoder == 0) {
            LastState = false;
        }
    }
    return 0;
}
