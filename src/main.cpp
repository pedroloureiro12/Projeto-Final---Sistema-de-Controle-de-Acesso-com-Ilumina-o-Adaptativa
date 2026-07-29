#include <Arduino.h>
#include "sistema.h"
#include "teclado.h"
#include "lcd.h"

char senhaAdmin[5] = "1234";
char senhasUsuarios[3][5] = {"1111", "2222", "3333"};
 



bool senhasIguais(const char* s1, const char* s2) {
  int i = 0;
  while (s1[i] != '\0' && s2[i] != '\0') {
    if (s1[i] != s2[i]) return false;
    i++;
    }
  return s1[i] == s2[i];
}


void mostrarTelaEspera();
void mostrarTelaSenha(const char* msg, Estados proxEstado);
void abrirTranca();
void acessoNegado();
void mostrarMenuAdmin();


void setup() {
 lcd_init();

  pinMode(PIN_TRANCA, OUTPUT);
  digitalWrite(PIN_TRANCA, LOW);

  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_BACKLIGHT, OUTPUT);

  inicializarTeclado();

  xTaskCreate(taskBrilho, "Brilho", 2048, NULL, 1, NULL);

  mostrarTelaEspera();

}



void loop() {

  char tecla = ler_teclado();
  if (!tecla) return;

  // Tecla '#' cancela e volta à espera (exceto se estiver dentro do menu admin)
  if (tecla == '#' && (estadoAtual == ENTRADA_USER || estadoAtual == ENTRADA_ADM)) {
    mostrarTelaEspera();
    return;
  }

  switch (estadoAtual) {
    case ESPERA:
      if (tecla == '*') mostrarTelaSenha("Senha Usuario:", ENTRADA_USER);
      if (tecla == '#') mostrarTelaSenha("Senha Admin:", ENTRADA_ADM);
      break;

    case ENTRADA_USER:
    case ENTRADA_ADM:
      if (tecla >= '0' && tecla <= '9' && indexEntrada < 4) {
        bufferEntrada[indexEntrada++] = tecla;
        
       
        lcd_write('*'); 
        
        if (indexEntrada == 4) {
          bufferEntrada[4] = '\0';
          delay(500);
          if (estadoAtual == ENTRADA_ADM) {
            // Usando a função manual senhasIguais
            if (senhasIguais(bufferEntrada, senhaAdmin)) mostrarMenuAdmin(); 
            else acessoNegado();
          } else {
            bool autorizado = false;
            for(int i=0; i<3; i++) { 
              if(senhasIguais(bufferEntrada, senhasUsuarios[i])) autorizado = true; 
            }
            if (autorizado) abrirTranca(); else acessoNegado();
          }
        }
      }
      break;

    case MENU_CONFIG:
      if (tecla == '1') {
        lcd_clear(); lcd_print("ID Usuario (1-3):");
        estadoAtual = ESCOLHER_ID_EDITAR;
      } else if (tecla == '2') {
        lcd_clear(); lcd_print("Tempo (1-9s):");
        estadoAtual = AJUSTAR_TEMPO;
      } else if (tecla == '3') {
        mostrarTelaSenha("Nova Senha ADM:", DEFINIR_NOVA_SENHA_ADM);
      } else if (tecla == '*') {
        mostrarTelaEspera();
      }
      break;

    case ESCOLHER_ID_EDITAR:
      if (tecla >= '1' && tecla <= '3') {
        usuarioAlvo = (tecla - '0') - 1;
        indexEntrada = 0;
        lcd_clear(); lcd_print("Nova Senha U"); lcd_write(tecla);
        lcd_set_cursor(0, 1);
        estadoAtual = DEFINIR_NOVA_SENHA_USER;
      }
      break;

    case DEFINIR_NOVA_SENHA_USER:
      if (tecla >= '0' && tecla <= '9' && indexEntrada < 4) {
        senhasUsuarios[usuarioAlvo][indexEntrada++] = tecla;
        
        // Mostra a tecla real no display
        lcd_write(tecla); 
        
        if (indexEntrada == 4) {
          senhasUsuarios[usuarioAlvo][4] = '\0';
          lcd_clear(); lcd_print("Salvo com Sucesso");
          delay(1500); mostrarMenuAdmin();
        }
      }
      break;

    case DEFINIR_NOVA_SENHA_ADM:
      if (tecla >= '0' && tecla <= '9' && indexEntrada < 4) {
        senhaAdmin[indexEntrada++] = tecla;
        
        // Mostra a tecla real no display
        lcd_write(tecla); 
        
        if (indexEntrada == 4) {
          senhaAdmin[4] = '\0';
          lcd_clear(); lcd_print("ADM Atualizado");
          delay(1500); mostrarMenuAdmin();
        }
      }
      break;

    case AJUSTAR_TEMPO:
      if (tecla >= '1' && tecla <= '9') {
        tempoTranca = tecla - '0';
        lcd_clear(); lcd_print("Tempo: "); lcd_write(tecla); lcd_print("s");
        delay(1500); mostrarMenuAdmin();
      }
      break;
  }
}