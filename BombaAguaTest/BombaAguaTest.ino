//Variables para la mini bomba de agua
int Input1 = 9;    // Control pin 1 for motor 1
int Input2 = 10;     // Control pin 2 for motor 1

int OnOff = 1; // Switch On/Off para la bomba (1 = On | 0 = Off)
int Adelante; // Variable PWM 1
int Atras; // Variable PWM 2
int Detener = map(0, 0, 1023, 0, 255);
int Var = 1022;


void setup() {
  Serial.begin(9600);

}

void loop() {
analogWrite(Input1,1022);

//analogWrite(Input2, 1022);


}
