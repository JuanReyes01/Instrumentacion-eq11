
#define Step 4      // pin STEP de A4988 a pin 4
#define Dir 5     // pin DIR de A4988 a pin 5
String ingreso;
int pasos;
/////////////////////////////////////////////////////////////////////////
void mover(){
  Serial.println ("Cuántos pasos desea dar, 1 paso equivale a 1.8°");
  ingreso  = Serial.readStringUntil('\n');
  pasos = ingreso.toInt ();
  Serial.println (pasos);
  if (pasos >=10)
  {
   digitalWrite(Dir, 1);     // giro en sentido opuesto
   for(int i = 0; i < pasos; i++){
    digitalWrite(Step, 1); 
    delay(10);
    Serial.println(i);
    digitalWrite(Step, 0);
    delay(10);
  }
    }
  else {
    mover();
    }      
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  pinMode(Step, OUTPUT);  // pin 4 como salida
  pinMode(Dir, OUTPUT);   // pin 5 como salida
  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  mover();
}
