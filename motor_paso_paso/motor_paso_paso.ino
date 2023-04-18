#include <PID_v1.h> // Incluir la librería PID_v1
#define Dir 10     // pin DIR de A4988 a pin 5
#define Step  11     // pin STEP de A4988 a pin 4
#define Enable 12
bool control = false;
int encoder_pin = 2;
int iteraciones = 0;
unsigned int rpm;
volatile byte pulses;
unsigned long Inicial = 0;
unsigned long Final = 0;
unsigned long interval = 100UL;
unsigned long del_unsigned = 1000000;
unsigned int pulses_per_turn = 20; // Depends on the number of spokes on the encoder wheel
int Encoder = 0;
int Estado = 1;
int Pulsos = 0;
int count = 0;
int PulsosRotacion = 20;
int paso = 0;
int del = 0;
int new_del = 0;
unsigned long InitialTime = 0;
unsigned long FinalTime;
float RPMs;
/////// PID CONTROL RPMS
//PID myPID(&RPMs, &new_del, &rpm_deseado, kp, ki, kd, DIRECT);
float rpm_deseado = 90;
void setup() {
  rpm = 0;
  pulses = 0;

  Serial.begin(9600);
  pinMode(Step, OUTPUT);  // pin 4 como salida
  pinMode(Dir, OUTPUT);   // pin 5 como salida
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, LOW);
  pinMode(encoder_pin, INPUT); // Setting encoder-1 pin as Input
  // attachInterrupt(digitalPinToInterrupt(encoder_pin), Encoder_fun, RISING);
  //myPID.SetOutputLimits(300, 20000); // Establecer límites de salida del control PID
  //myPID.SetMode(AUTOMATIC); // Configurar el modo de control PID como automático
}

void loop() {
  Serial.print('RPM DESEADO');
  Serial.println(rpm_deseado);
  Serial.print('RPM ACTUAL');
  Serial.println(RPMs);
  
  if (Serial.available() > 0) { // Verificar si hay datos disponibles en el buffer serial
    float rpm_deseado = Serial.parseInt(); // Leer el entero recibido
    if (rpm_deseado >= 100.0) {
      new_del = int((-0.836 * log(rpm_deseado) + 5.2281) * 1000);
    }
    else {
      new_del = int((-4.367 * log(rpm_deseado) + 20.528) * 1000);
    }
    Serial.println(rpm_deseado);
    Serial.println(new_del);
  }
  del_unsigned = (unsigned long)new_del;
  Inicial = millis();
  if ((Inicial - Final) > (del_unsigned/1000)) {
    if ( paso == 1) {
      paso = 0;
    }
    else if (paso == 0) {
      paso = 1;
    }
    digitalWrite(Step, paso);
    Final = Inicial;
  }
  Encoder = digitalRead(encoder_pin);
  //Serial.println(new_del);
  if (Encoder == LOW && Estado == 1)
  {
    Estado = 0;
  }

  if (Encoder == HIGH && Estado == 0)
  {
    Pulsos++;
    Estado = 1;
  }

  if (Pulsos == PulsosRotacion)
  {
    FinalTime = millis();
    RPMs = 60000 / (FinalTime - InitialTime);
    Pulsos = 0;
    InitialTime = FinalTime;
    Serial.println(RPMs);
    control = true;
  }

  if ((rpm_deseado == RPMs) && (control == true)) {
    Serial.println("SI");
    control = false;
  }

  if ((rpm_deseado != RPMs) && (iteraciones == 10) && (control==true)) {
    if (rpm_deseado > RPMs) {

      new_del --;
    }
    if (rpm_deseado < RPMs) {
      new_del ++;
    }
    iteraciones = 0;
  }
  iteraciones ++;
  //Serial.println(rpm_deseado);
}
