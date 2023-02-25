#include "HX711.h"

//Variables
#define DOUT  A1
#define CLK  A0
HX711 balanza(DOUT, CLK);

void setup() {
  Serial.begin(9600);

}

void loop() {

 Serial.println(balanza.read_average(10));

}
