#include <Arduino.h>
#include "SevSeg.h"
SevSeg sevseg; 
int banca =0, bancaAnt = 0;
#define moneda1Pin  A5
#define moneda2Pin  A4
#define moneda5Pin  A2
#define moneda10Pin A0

int moneda1, moneda1Ant,
    moneda2, moneda2Ant,
    moneda5, moneda5Ant,
    moneda10, moneda10Ant;

void setup() {
  Serial.begin(9600); //Configuracion de la velocidad serial
  pinMode(moneda1, INPUT);
  pinMode(moneda2, INPUT);
  pinMode(moneda5, INPUT);
  pinMode(moneda10, INPUT);
   byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop() {
  moneda1 = analogRead(moneda1Pin);
  if (moneda1 >= 100) {
      banca++;
      delay(1000);
  }
  moneda1Ant = moneda1;
  
  moneda2 = analogRead(moneda2Pin);
  if (moneda2 >= 100) {
      banca=banca+2;
      delay(1000);
  }
  moneda2Ant = moneda2;

  moneda5 = analogRead(moneda5Pin);
  if (moneda5 >= 100) {
      banca=banca+5;
      delay(1000); 
      
  }
  moneda5Ant = moneda5;

  moneda10 = analogRead(moneda10Pin);
  if (moneda10 >= 100) {
      banca=banca+10;
      delay(1000); 
  }

  moneda10Ant = moneda10;
  if (banca != bancaAnt) {
     Serial.print("Lectura: "); 
     Serial.println(banca);

  }
  bancaAnt = banca;
  sevseg.setNumber(banca);
  sevseg.refreshDisplay(); 
}
