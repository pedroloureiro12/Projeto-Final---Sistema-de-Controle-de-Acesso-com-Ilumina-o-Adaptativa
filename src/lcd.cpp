#include <Arduino.h>
#include "lcd.h"

void lcd_pulse_enable(){

    digitalWrite(LCD_E, HIGH);
    delayMicroseconds(1);
    digitalWrite(LCD_E, LOW);
    delayMicroseconds(100);
}

void lcd_send_4bits(uint8_t valor){
    
    digitalWrite(LCD_D4, (valor>>0) & 0x01);
    digitalWrite(LCD_D5, (valor>>1) & 0x01);
    digitalWrite(LCD_D6, (valor>>2) & 0x01);
    digitalWrite(LCD_D7, (valor>>3) & 0x01);
    lcd_pulse_enable();

}

void lcd_send(uint8_t valor, uint8_t modo){

    digitalWrite(LCD_RS, modo);
    lcd_send_4bits(valor >> 4);
    lcd_send_4bits(valor & 0x0F);

}

void lcd_command(uint8_t cmd){

    lcd_send(cmd, LOW);

}

void lcd_write(uint8_t data){

    lcd_send(data, HIGH);

}

void lcd_print(const char* s){

    
    while (*s)
    {
        lcd_write(*s++);
    }
}

void lcd_set_cursor(uint8_t col, uint8_t row){
    lcd_command(0x80 | (col + (row ? 0x40 : 0x00)));
}

void lcd_clear(){

    lcd_command(0x01);
    delay(2);
}

void lcd_init(){
    pinMode(LCD_RS, OUTPUT);
    pinMode(LCD_D4, OUTPUT);
    pinMode(LCD_D6, OUTPUT);
    pinMode(LCD_E, OUTPUT);
    pinMode(LCD_D5, OUTPUT);
    pinMode(LCD_D7, OUTPUT);
    pinMode(PIN_BACKLIGHT, OUTPUT);
    digitalWrite(PIN_BACKLIGHT, HIGH);

    delay(50);

    lcd_send_4bits(0x03);
    delay(5);
    lcd_send_4bits(0x03);
    delay(1);
    lcd_send_4bits(0x03);
    lcd_send_4bits(0x02);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_clear();


}

void taskBrilho(void* pvParameters){

    while(true){

        int valorLDR = analogRead(PIN_LDR);

        int brilho = map(valorLDR,0,4095, 10,255);

        analogWrite(PIN_BACKLIGHT, brilho);

        vTaskDelay(100/portTICK_PERIOD_MS);

    }
}

void atualizarBrilhoLCD(){

int valorLDR = analogRead(PIN_LDR);
int brilho = map(valorLDR, 0, 4095, 255, 10);

analogWrite(PIN_BACKLIGHT, brilho);


}