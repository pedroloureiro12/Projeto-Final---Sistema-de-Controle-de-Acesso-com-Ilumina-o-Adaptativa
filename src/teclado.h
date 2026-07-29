#ifndef _TECLADO_H_
#define _TECLADO_H_

#include <Arduino.h>


#define LIN_1 35
#define LIN_2 37
#define LIN_3 36
#define LIN_4 38
#define COL_1 41
#define COL_2 40
#define COL_3 39

#define PIN_LDR 9

void inicializarTeclado();

char ler_teclado();



#endif