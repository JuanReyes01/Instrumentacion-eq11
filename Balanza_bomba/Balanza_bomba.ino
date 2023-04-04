// Librerias
#include "HX711.h"
// Pines
#define canal_a  9
#define canal_b  10
#define DOUT  A1
#define CLK  A0
HX711 balanza(DOUT, CLK);
// Variables
bool inicio = true;
String ingreso ;
float peso_deseado = 0;
float anadir = 0;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void servir(float peso, float peso_ant,int pwm, int adicion, float porc1, float porc2, float porc3){
  valido = true; 
  if (abs(peso) -abs( peso_ant) >= 20){
        Serial.println("invalido");
        analogWrite(canal_a,0);
        delay(1500);
        valido = false;
        }  
  if (valido == true){
    if (peso_deseado*porc1 >= peso)
      analogWrite(canal_a,255);
  if (peso_deseado*porc1 < peso <= peso_deseado*porc2)
      analogWrite(canal_a,pwm);  
  if (peso>= peso_deseado*porc3){
        Serial.println("parar");
        analogWrite(canal_a,0);
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
void preguntar(){
  Serial.println ("Empiece  a agregar el soluto");
  float peso = balanza.get_units(4); // Entrega el peso actualment medido en gramos
  peso = -peso + 580+ anadir;
  ingreso = Serial.readString();
  Serial.println(ingreso);
  masa = peso;
  Serial.print("masa: ");
  Serial.println (masa);
  if (ingreso == "SI")
  {
   ; 
    }
  else {
    preguntar();
    }      
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void preguntar_peso(){
  Serial.println ("Peso a comlpetar: ");
  peso_deseado = Serial.read();
  Serial.println(peso_deseado);
  if (peso_deseado <10)
      {preguntar_peso();
      
      }
  else {
    ;}
  }  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
void setup() {
  // put your setup code here, to run once:
  balanza.set_scale(1084.9);
  Serial.begin(9600);
  pinMode(canal_a,OUTPUT);
  pinMode(canal_b, OUTPUT);
  delay(3000);
  pesito = balanza.get_units(20); // Entrega el peso actualment medido en gramos
  anadir = pesito-580;
  preguntar();
  preguntar_peso();
  Serial.println("Dispensando");
  //Serial.println(anadir);
  peso_ant = balanza.get_units(4) - 580 -anadir;
  Serial.println("Peso a completar");
  Serial.println(peso_deseado);
  definir_variables(peso_deseado);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  float peso = balanza.get_units(4); // Entrega el peso actualment medido en gramos
  peso = -peso + 580+ anadir;
  Serial.println(peso,1);
  if (inicio == true){ 
  servir(peso, peso_ant,pwm,adicion,porc1,porc2,porc3);  
  }
  peso_ant = peso;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
