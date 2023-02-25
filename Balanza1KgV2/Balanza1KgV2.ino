#include "HX711.h"

//Variables
#define DOUT  A1
#define CLK  A0
HX711 balanza(DOUT, CLK);

void setup() {
  balanza.set_scale(1084.9);
  Serial.begin(9600);

}

void loop() {

  float peso = balanza.get_units(10); // Entrega el peso actualment medido en gramos
  if(peso<0) peso = peso*-1;
  peso = peso-536.5;
  
  Serial.print("Peso: ");
  Serial.print(peso,2);
  Serial.println(" g");
  delay(100);

}
