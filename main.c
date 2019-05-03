#include "Config.h"
#include <xc.h>
#include <stdbool.h>


//---------------------------- MAIN CODE ---------------------------------------

int main() {   
    ConfigInit(); 
    StopMotor();
    configurarHorario();
    configurarAntiHorario();

    while (1) {

        keypress = KeyPadGetKey();

        //Si se presiona una tecla
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

        // Si se presenta un pulso del encoder
        if (pinEncoder == 1 && LastState == false) {
            Encoder();
        } else if (pinEncoder == 0) {
            LastState = false;
        }
    }
    return 0;
}
