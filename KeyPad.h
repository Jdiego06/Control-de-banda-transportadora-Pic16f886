#ifndef KEY_PAD_H
#define  KEY_PAD_H

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <xc.h>

/*    KeyPad Pins    */
#define row1 RA0
#define row2 RA1
#define row3 RA2
#define row4 RA4
#define col1 RA3
#define col2 RA5
#define col3 RA7
#define col4 RA6 


extern const int keyPadMatrix[];

int KeyPadGetKey(void);

#endif