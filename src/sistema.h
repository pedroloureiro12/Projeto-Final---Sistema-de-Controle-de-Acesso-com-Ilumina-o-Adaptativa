#ifndef _SISTEMA_H_
#define _SISTEMA_H_

#include <Arduino.h>


enum Estados { 
  ESPERA, 
  ENTRADA_USER, 
  ENTRADA_ADM, 
  MENU_CONFIG, 
  ESCOLHER_ID_EDITAR, 
  DEFINIR_NOVA_SENHA_USER, 
  DEFINIR_NOVA_SENHA_ADM, 
  AJUSTAR_TEMPO 
};


extern Estados estadoAtual;
extern char bufferEntrada[5];
extern int indexEntrada;
extern int usuarioAlvo;
extern int tempoTranca;


#define PIN_TRANCA 42

void mostrarTelaEspera();

void mostrarTelaSenha(const char* msg, Estados ProxEstado);

void abrirTranca();

void acessoNegado();

void mostrarMenuAdmin();






#endif