#ifndef _LCD_H_
#define _LCD_H_

#include <Arduino.h>
#define LCD_RS 3
#define LCD_E  8
#define LCD_D4 18
#define LCD_D5 17
#define LCD_D6 16
#define LCD_D7 15
#define PIN_BACKLIGHT 4
#define PIN_LDR 9

void lcd_pulse_enable();

void lcd_send_4bits(uint8_t valor);

void lcd_send(uint8_t valor, uint8_t modo);

void lcd_command(uint8_t cmd);

void lcd_write(uint8_t data);

void lcd_print(const char* s);

void lcd_set_cursor(uint8_t col, uint8_t row);

void lcd_clear();

void lcd_init();

void taskBrilho(void* pvParameters);

void atualizarBrilhoLCD();

#endif