#ifndef KEY_PAD_H
#define  KEY_PAD_H

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>


const int keyPadMatrix[] = {
    'A', '1', '2', '3',
    'B', '4', '5', '6',
    'C', '7', '8', '9',
    'D', '*', '0', '#',
    0xFF
};

char key, old_key;

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

#endif