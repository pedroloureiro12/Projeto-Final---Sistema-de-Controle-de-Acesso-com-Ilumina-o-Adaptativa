#include <Arduino.h>
#include "sistema.h"
#include "lcd.h"

Estados estadoAtual = ESPERA;

char bufferEntrada[5];
int indexEntrada = 0;
int usuarioAlvo = -1;
int tempoTranca = 3;
 
void mostrarTelaEspera(){

    estadoAtual = ESPERA;
    indexEntrada = 0;
    lcd_clear();
    lcd_print("*: abrir porta");
    lcd_set_cursor(0,1);
    lcd_print("#: configuracoes");
}

void mostrarTelaSenha(const char* msg, Estados ProxEstado){

    estadoAtual = ProxEstado;
    indexEntrada = 0;
    lcd_clear();
    lcd_print(msg);
    lcd_set_cursor(0,1);
}

void abrirTranca(){

    lcd_clear();
    lcd_print("acesso liberado");
    digitalWrite(PIN_TRANCA, HIGH);
    delay(tempoTranca * 1000);
    digitalWrite(PIN_TRANCA, LOW);
    mostrarTelaEspera();

}

void acessoNegado(){
    lcd_clear();
    lcd_print("acesso negado");
    delay(1000);
    mostrarTelaEspera();
}

void mostrarMenuAdmin(){
    estadoAtual = MENU_CONFIG;
    lcd_clear();
    lcd_print("1: User 2 :Tempo");
    lcd_set_cursor(0,1);
    lcd_print("3: Senhaadm *:Sair");
}


