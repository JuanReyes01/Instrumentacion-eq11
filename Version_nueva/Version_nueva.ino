#include <Arduino.h>
# include <analogWrite.h>
#include <Wire.h>
#include "HX711.h"
// Pines Motobomba
#define canal_a  14
#define canal_b  12
// Pines Bal
#define DOUT  26
#define CLK  27
HX711 balanza(DOUT, CLK);
//#define encoder_pin 13
// Variables
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void definir_variables(float peso_deseado){
  if(peso_deseado <=50) {
    Serial.println("MENOR A 50");
    pwm = 180;
    adicion = 0;
    porc1 = 0.8;
    porc2 = 0.9;
    porc3 = 0.93;
    }
  else if( (50< peso_deseado) && (peso_deseado <= 100)) {
    Serial.println("ENTRE 50 Y 100");
    pwm = 180;
    adicion = 1;
    porc1 = 0.8;
    porc2 = 0.9;
    porc3 = 0.95;
  }
  else if((100 < peso_deseado)&& (peso_deseado <= 150)) {
    Serial.println("ENTRE 100 Y 200");
    pwm = 180;
    adicion = 1;
    porc1 = 0.8;
    porc2 = 0.9;
    porc3 = 0.965;
  }
  else if((150 < peso_deseado)&& (peso_deseado <= 200)) {
    Serial.println("ENTRE 100 Y 200");
    pwm = 180;
    adicion = 1;
    porc1 = 0.8;
    porc2 = 0.9;
    porc3 = 0.975;
  }
  else if((200 < peso_deseado)&& (peso_deseado <= 300)) {
    Serial.println("ENTRE 200 Y 300");
    pwm = 180;
    adicion = 0;
    porc1 = 0.8;
    porc2 = 0.9;
    porc3 = 0.985;
  }

  else {
    pwm = 180;
    adicion = 0;
    porc1 = 0.8;
    porc2 = 0.90;
    porc3 = 0.98;
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
    peso_ant = balanza.get_units(4) - peso_inicial;
    agregar = true;
    }
  } 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void agregar_soluto(){
  peso = balanza.get_units(10) - peso_inicial; // Entrega el peso actualment medido en gramos
  //Serial.println(peso);
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
void preguntar_rpms(){
  Serial.println("Introduzca las RPMs a las que desea mezclar"); 
  String rpm_string = Serial.readString();
  rpm_deseado = rpm_string.toInt();
  if (rpm_deseado <10){
      preguntar_rpms(); }    
  else {
    Serial.print("RPMs deseadas: ");
    Serial.println(rpm_deseado);
    Wire.beginTransmission(0x23); // transmit to device #8
    Wire.write((uint8_t*)&rpm_deseado, sizeof(rpm_deseado)); // Send integer value to slave
    Wire.endTransmission(); // End transmission
    }
  } 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void agregar_solvente(float peso, float peso_ant,int pwm, int adicion, float porc1, float porc2, float porc3){
  Serial.println ("Debe agregar el solvente");
  valido = true; 
  if (abs(peso) -abs( peso_ant) >= 20){
        Serial.println("invalido");
        analogWrite(canal_b,0);
        delay(20);
        valido = false;
        }  
  if (valido == true){
    if (peso_deseado*porc1 >= peso)
      //digitalWrite(canal_b,HIGH);
      analogWrite(canal_b,250);
    if (peso_deseado*porc1 < peso <= peso_deseado*porc2)
      //digitalWrite(canal_b,HIGH);
      //digitalWrite(Step, 0);
      analogWrite(canal_b, 200);
    if (peso>= peso_deseado*porc3){
        analogWrite(canal_b,0);
        Serial.println("Mayor, mezclando ");
        agregar = false;
        iniciar_mezclar = true;
        //preguntar_rpms();
    } 
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  balanza.set_scale(1084.9);
  Serial.begin(9600);
  pinMode(canal_a,OUTPUT);
  pinMode(canal_b, OUTPUT);
  peso_inicial = balanza.get_units(40); // No se por que carajo el peso estaba llegando negativo pero weno
  Serial.println(peso_inicial);
  Serial.println ("CALIBRADO");
  Wire.begin(); // join i2c bus (address optional for master)

 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() { 
  peso = balanza.get_units(4) - peso_inicial; // Entrega el peso actualment medido en gramos
  Serial.print("Masa actual: "); 
  Serial.println(peso); 
  //Serial.println(agregar);

  if (agregar == true){    
    agregar_solvente(peso, peso_ant,pwm,adicion,porc1,porc2,porc3);  
    }
  peso_ant = peso;
  
  if (Serial.available() > 0){
      int comando = Serial.readString().toInt();
      Serial.println(comando);
   
    if (comando == 1){ // Volver a mandar rpm del motor
      preguntar_rpms();
    }
    else if (comando == 2){ //Volver a servir liquido
      agregar==true;
      peso_acumulado = peso;
      //peso_inicial = (balanza.get_units(20)); // Entrega el peso actualment medido en gramos
      preguntar_solvente();
      }
    else if (comando  == 3){ // Volver a tarar
      peso_acumulado = peso;
      peso_inicial = (balanza.get_units(20)); // Entrega el peso actualment medido en gramos
      agregar_soluto();
      }
  }
}
