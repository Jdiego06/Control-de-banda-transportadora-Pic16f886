#ifndef CONFIG_H
#define CONFIG_H

#include "main.h"
#include <stdbool.h>
#include <xc.h>
#include <stdio.h>
#include "KeyPad.h"
#include "Lcd.h"


/*---------------------------------------------------------------------------------------
 *			Displacement constant: RollDiameter/PulsesPerTurnEncoder
 *                      Ej: 35Cm/36Pulses = 0.97
 * --------------------------------------------------------------------------------------*/
#define CteVueltas 0.97

/*    System pins    */
#define pinEncoder RB0
#define MotorHorario RC0
#define MotorAntiHorario RC1
  

void ConfigInit(void);
int RunMotor(void);
int StopMotor(void);
int configurarAntiHorario(void);
int configurarHorario(void);
int VerificarInversionGiro(void);
int Encoder(void);
void testFn(void);

#endif