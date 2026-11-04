#include <Arduino.h>
const int pinADC = A0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    int lectura = analogRead(pinADC);       // 0 a 1023
    int brillo = map(lectura, 0, 1023, 0, 100);
    Serial.write(brillo); 
  	delay(1000);
    lectura = analogRead(1);
    brillo = map(lectura, 0, 1023, 101, 200);
    Serial.write(brillo); 


    delay(50);
}