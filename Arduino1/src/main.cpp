#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



// Dirección I2C: 0x27 (puede variar)
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Adafruit_LiquidCrystal lcd(0);
unsigned long tiempoAnterior = 0;
unsigned int contador = 0;

void setup()
{
    //lcd.begin(16, 2);
  
    lcd.init();
    lcd.backlight();
    lcd.clear();
    delay(100);
    

    lcd.setCursor(0, 0);
    lcd.print("Hardware Digital");

    lcd.setCursor(0, 1);
    lcd.print("Comunicacion I2C");

    delay(5000);  

    Serial.begin(9600);
  
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ADC0:   %");
    lcd.setCursor(0, 1);
    lcd.print("ADC1:   %");
}

void loop()
{
 if (Serial.available() > 0) {
        byte brillo = Serial.read();
   		lcd.setCursor(5, 0);
        if (brillo>100){
   			lcd.setCursor(5, 1);
            brillo =brillo- 100;
        }
   		if (brillo<100){
        	lcd.print(0);	
        }
        if (brillo<10){
        	lcd.print(0);	
        }
        lcd.print(brillo);
    }
}