#include <stdio.h>
#include <stdlib.h>
#include <xc.h>


#define row1 RA0
#define row2 RA1
#define row3 RA2
#define row4 RA3

#define col1 RA4
#define col2 RA5
#define col3 RA6
#define col4 RA7 


const int keyPadMatrix[] = {
    '7', '8', '9', '/',
    '4', '5', '6', '*',
    '1', '2', '3', '-',
    'N', '0', '=', '+',
    0xFF
};

char key, old_key;

void KeyPadInit() {
    TRISA = 0xf0;
    PORTA = 0x00;
}

int KeyPadGetKey() {
    // This routine returns the first key found to be pressed during the scan.
    char key = 0, row;

    for (row = 0b00000001; row < 0b00010000; row <<= 1) {
        { // turn on row output
            row1 = (row & 0x0001) >> 0;
            row2 = (row & 0x0002) >> 1;
            row3 = (row & 0x0004) >> 2;
            row4 = (row & 0x0008) >> 3;
            __delay_ms(1);
        }
        // read colums - break when key press detected
        if (col1)break;
        key++;
        if (col2)break;
        key++;
        if (col3)break;
        key++;
        if (col4)break;
        key++;
    }
    row1 = 0;
    row2 = 0;
    row3 = 0;
    row4 = 0;
    if (key != old_key) {
        old_key = key;
        return keyPadMatrix[ key ];
    } else
        return keyPadMatrix[ 0x10 ];
}


