#include <PID_v1.h> // Incluir la librería PID_v1
#define Dir 10     // pin DIR de A4988 a pin 5
#define Step  11     // pin STEP de A4988 a pin 4
#define Enable 12
int encoder_pin=2;
int iteraciones = 0;
unsigned int rpm;
volatile byte pulses;
unsigned long time_old;
unsigned int pulses_per_turn= 20; // Depends on the number of spokes on the encoder wheel
int Encoder = 0;
int Estado = 1;
int Pulsos = 0;
int count = 0;
int PulsosRotacion = 20;
int del = 0;
int new_del =0;
unsigned long InitialTime = 0;
unsigned long FinalTime; 
float RPMs;
/////// PID CONTROL RPMS
//PID myPID(&RPMs, &new_del, &rpm_deseado, kp, ki, kd, DIRECT);
float rpm_deseado = 90;
void setup() {
  rpm=0;
  pulses=0;
  time_old=0;
  
  Serial.begin(9600);
  pinMode(Step, OUTPUT);  // pin 4 como salida
  pinMode(Dir, OUTPUT);   // pin 5 como salida
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, LOW);
  pinMode(encoder_pin,INPUT); // Setting encoder-1 pin as Input 
 // attachInterrupt(digitalPinToInterrupt(encoder_pin), Encoder_fun, RISING);
  //myPID.SetOutputLimits(300, 20000); // Establecer límites de salida del control PID
  //myPID.SetMode(AUTOMATIC); // Configurar el modo de control PID como automático
}

 void loop(){
  if (Serial.available() > 0) { // Verificar si hay datos disponibles en el buffer serial
    float rpm_deseado = Serial.parseInt(); // Leer el entero recibido
  if (rpm_deseado >= 100){
    new_del = int((-0.836*log(rpm_deseado) + 5.2281)*1000);
    }
  else{
    new_del = int((-4.367*log(rpm_deseado) + 20.528)*1000);
    }
  Serial.println(new_del);
  }
  Serial.println("Mover");
  digitalWrite(Step, 1); 
  delayMicroseconds(new_del);
  digitalWrite(Step, 0);
  delayMicroseconds(new_del); //delayMicroseconds
  Encoder = digitalRead(encoder_pin);  
  //Serial.println(new_del);
  if(Encoder == LOW && Estado == 1)
  {
     Estado = 0;             
  }

  if(Encoder == HIGH && Estado == 0)
  {
    Serial.println("HIGH");
     Pulsos++; 
     Estado = 1;     
  }

  if(Pulsos == PulsosRotacion)
  {
    FinalTime = millis();
    RPMs = 60000/(FinalTime - InitialTime);
    Pulsos = 0; 
    InitialTime = FinalTime;
    Serial.print("RPM = ");
    Serial.println(RPMs); 
    digitalWrite(Encoder, HIGH);
  }
   if ((rpm_deseado != RPMs) && (iteraciones == 4)){
    if (rpm_deseado > RPMs){
       
      new_del --;
      }
    if (rpm_deseado < RPMs){
      //Serial.println("Menor");
      new_del ++;
      }    
      iteraciones = 0;
 }
  iteraciones ++;
  //Serial.println(rpm_deseado);
}

 
