// Librerias
#include "HX711.h"
// Pines
#define canal_a  6
#define canal_b  5
#define DOUT  A1
#define CLK  A0
#define Dir 2     // pin DIR de A4988 a pin 5
#define Step 3      // pin STEP de A4988 a pin 4
#define Enable 4
HX711 balanza(DOUT, CLK);
// Variables
int pasos;
bool inicio = false;
float peso_deseado = 0;
float peso_inicial = 0;
float peso = 0;
int pwm;
int adicion;
float masa;
float porc1;
float porc2;
float porc3;
float peso_ant;
float pesito;
bool valido;
bool continuar = false;
bool iniciar_mezclar = false;
int rpm_deseado = 0;
int del = 0;
bool agregar = false;
float peso_acumulado = 0;

/////////////////////////////////////////////////////////////////////////
/* IDEA: USAR UN INTERRUPT BASADO EN TIEMPO DE MANERA QUE CUANDO PASE EL DELAY QUE QUIERO, HACE EL STEP
 * EJ:
 * FUNCION ASOCIADA AL INTERRUPT:
 * void mover_motor(){
    if ( paso == 1) {
      paso = 0;
    }
    else if (paso == 0) {
      paso = 1;
    }
    digitalWrite(Step, paso);
  }}
 ACTIVACION DEL INTERRUPT:
 Inicial = millis();
 if ((Inicial - Final) > (tiempo_paso)){
 mover_motor();
 Final = Inicial;
 } 
 ESTO NO LO HE HECHO PERO PODRIA SERVIR PARA INTEGRAR EL MOVIMIENTO DEL MOTOR CON EL RESTO DE COSAS
 */
void mezclar(int rpm_deseado){
  /*while (true){
    if(Serial.available() > 0){
    String comando = Serial.readString();
    }
    del = rpm_deseado; //Poner aqui la funcion de conversion a delay
    digitalWrite(Step, 1); 
    delay(del);  // Cambiar del por delayMicroseconds
    digitalWrite(Step, 0);
    delay(del);  // Cambiar del por delayMicroseconds  
    }*/
    /*
    del = 2000; // microsegundos
    
    digitalWrite(Step, 1); 
    delayMicroseconds(del);  // Cambiar del por delayMicroseconds
    digitalWrite(Step, 0);
    delayMicroseconds(del);  // Cambiar del por delayMicroseconds  
    String ingreso = Serial.readString();
    Serial.print("Ingreso: ");
    Serial.println(ingreso);
    if(ingreso!="")
    {
       mezclar(rpm_deseado);
      }
    else {
      ;
      }    */  
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void agregar_solvente(float peso, float peso_ant,int pwm, int adicion, float porc1, float porc2, float porc3){
  Serial.println ("Debe agregar el solvente");
  valido = true; 
  if (abs(peso) -abs( peso_ant) >= 20){
        Serial.println("invalido");
        //analogWrite(canal_a,0);
        //delay(1500);
        valido = false;
        }  
  if (valido == true){
    if (peso_deseado*porc1 >= peso)
      analogWrite(canal_b,255);
  if (peso_deseado*porc1 < peso <= peso_deseado*porc2)
      analogWrite(canal_b,pwm); 
      //digitalWrite(Step, 0);
  if (peso>= peso_deseado*porc3){
        analogWrite(canal_b,0);
        Serial.println("Mayor, mezclando ");
        digitalWrite(Enable, LOW); //el motor es activo bajo
        agregar = false;
        iniciar_mezclar = true;
        preguntar_rpms();
    } 
  }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
float definir_variables(float peso_deseado){
  if(peso_deseado <=50) {
    Serial.println("MENOR A 50");
    pwm = 180;
    adicion = 0;
    porc1 = 0.5;
    porc2 = 0.6;
    porc3 = 0.73;
    }
  else if( (50< peso_deseado) && (peso_deseado <= 100)) {
    Serial.println("ENTRE 50 Y 100");
    pwm = 180;
    adicion = 1;
    porc1 = 0.5;
    porc2 = 0.7;
    porc3 = 0.89;
  }
  else if((100 < peso_deseado)&& (peso_deseado <= 200)) {
    Serial.println("ENTRE 100 Y 200");
    pwm = 180;
    adicion = 1;
    porc1 = 0.7;
    porc2 = 0.85;
    porc3 = 0.96;
  }
  else if((200 < peso_deseado)&& (peso_deseado <= 300)) {
    Serial.println("ENTRE 200 Y 300");
    pwm = 180;
    adicion = 0;
    porc1 = 0.7;
    porc2 = 0.85;
    porc3 = 0.98;
  }

  else {
    pwm = 180;
    adicion = 0;
    porc1 = 0.8;
    porc2 = 0.90;
    porc3 = 0.98;
    }
    }    

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void agregar_soluto(){
  peso = -balanza.get_units(10); // Entrega el peso actualment medido en gramos
  //Serial.println(peso);
  peso = peso - peso_inicial;
  String ingreso = Serial.readString();
  Serial.print("Ingreso: ");
  Serial.println(ingreso);
  Serial.print("Masa del soluto: ");
  Serial.println(peso);
  if(ingreso!="")
  {
     preguntar_solvente();
    }
  else {
    agregar_soluto();
    }      
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void preguntar_solvente(){
  continuar = false;
  Serial.println("Introduzca el peso que desea completar con el solvente"); 
  String peso_string = Serial.readString();
  peso_deseado = peso_string.toInt();
  if (peso_deseado <10){
      preguntar_solvente(); }    
  else {
    Serial.print("Peso a completar: ");
    Serial.println(peso_deseado);
    definir_variables(peso_deseado);
    peso_ant = -balanza.get_units(4) - peso_inicial;
    agregar = true;
    }
  } 
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void preguntar_rpms(){
  Serial.println("Introduzca las RPMs a las que desea mezclar"); 
  String rpm_string = Serial.readString();
  rpm_deseado = rpm_string.toInt();
  if (rpm_deseado <10){
      preguntar_rpms(); }    
  else {
    Serial.print("RPMs deseadas: ");
    Serial.println(rpm_deseado);
    mezclar(peso_deseado);
    }
  } 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
void setup() {
  // put your setup code here, to run once:
  balanza.set_scale(1084.9);
  Serial.begin(115200);
  pinMode(canal_a,OUTPUT);
  pinMode(canal_b, OUTPUT);
  pinMode(Step, OUTPUT);  // pin 4 como salida
  pinMode(Dir, OUTPUT);   // pin 5 como salida
  pinMode(Enable, OUTPUT);
  digitalWrite(Enable, HIGH);
  peso_inicial = -balanza.get_units(20); // No se por que carajo el peso estaba llegando negativo pero weno
  Serial.println(peso_inicial);
  Serial.println ("Comience a agregar el soluto e ingrese '1' si desea iniciar a agregar el solvente");
  agregar_soluto();
  Serial.println("Dispensando");
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {  
  peso = -balanza.get_units(4) - peso_inicial; // Entrega el peso actualment medido en gramos
  Serial.print("Masa actual: "); 
  Serial.println(peso); 
  
  if (agregar == true){
    
    agregar_solvente(peso, peso_ant,pwm,adicion,porc1,porc2,porc3);  
    }
  peso_ant = peso;
  
  if (Serial.available() > 0){
      String comando = Serial.readString();
   if (comando == "M"){ // Volver a mandar rpm del motor
    preguntar_rpms();
    }
  if (comando == "L"){ //Volver a servir liquido
    peso_acumulado = peso;
    peso_inicial = -balanza.get_units(20); // Entrega el peso actualment medido en gramos
    preguntar_solvente();
    }
  if (comando == "P"){ // Volver a pesar soluto
    peso_acumulado = peso;
    peso_inicial = -balanza.get_units(20); // Entrega el peso actualment medido en gramos
    agregar_soluto();
    }

    }

}

