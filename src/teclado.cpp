#include <Arduino.h>
#include "teclado.h"

const int pinosLinhas[4] = {LIN_1, LIN_2, LIN_3, LIN_4};
const int pinosColunas[3] = {COL_1, COL_2, COL_3};
char mapaTeclas[4][3] = 
{{'1','2','3'},
 {'4','5','6'},                        
 {'7','8','9'},         
 {'*','0','#'}};


void inicializarTeclado(){

     for(int i=0; i<3; i++) {
    pinMode(pinosColunas[i], OUTPUT);
    digitalWrite(pinosColunas[i], HIGH);
  }
    for (int l = 0; l < 4; l++) {
    pinMode(pinosLinhas[l], INPUT_PULLUP);
}
}

char ler_teclado(){

    for (int c = 0; c < 3; c++)
    {
        digitalWrite(pinosColunas[c], HIGH);
        delayMicroseconds(100);

        for (int l = 0; l < 4; l++)
        {
            if (digitalRead(pinosLinhas[l])==HIGH)
            {
                delay(50);
                while(digitalRead(pinosLinhas[l]) == HIGH);

                digitalWrite(pinosColunas[c], LOW);
                delayMicroseconds(100);

                return mapaTeclas[l][c];

            }
        }
        digitalWrite(pinosColunas[c], LOW);
        delayMicroseconds(50);

    }
    return 0;
}

