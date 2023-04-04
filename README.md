# Instrumentacion-eq11
## Integrantes:
* Guerrero Rios Sebastian 
* Guayacan Mesa Sebastian 
* Ramirez Cepeda Yaisa Catalina
* Reyes Corredor Juan Camilo

## Materiales utilizados

### L293D
Driver para 2 motores DC

* In1: Pin9 Arduino
* In2: Pin10 Arduino
* Out1: Cable rojo motobomba
* Out2: Cable negro motobomba
* En1: 5V
* VCC: 5V
* Vss: 12V
* Pin 4 y 5: GND

### HX711
Conversor ACDC para celda de carga

* E+: Red
* E-: Black
* A+: Withe
* A-: Green
* Dt: Pin A1 arduino
* Sck: Pin A0 arduino
* Vcc: 5V

### A4988
Driver para motor paso a paso
* Dir: Pin 5 arduino
* Step: Pin 4 arduino
* Vdd: 5V
* Reset y Sleep van conectados entre si
* 2B: Black 
* 2A: Green
* 1A: Blue
* 1B: Red
* Vmot: Alimentación motor (15V)

### NEMA 17HS4401s
Motor paso a paso con resolución de 1.8°
* Black: 2B
* Green: 2A
* Blue: 1A
* Red: 1B

### Bomba de agua
*Red: Out1 L293D
* Black: Out2 L293D
### Celda de carga
* Red: E+
* Black: E-
* Withe: A+
* Green: A-

### Arduino Uno
* Pin9 Arduino: In1 L293D
* Pin10 Arduino: In2 L293D
* Pin 5 arduino: Dir A4988 
* Pin 4 arduino: Step A4988
* Pin A1 arduino: Dt HX711
* Pin A0 arduino: Sck HX711

## Códigos presentes en el repo:
* Balanza_Bomba:
Por medio de la consola le pide al usuario que indique la cantidad de masa que desea al final de la mezcla, incluyendo soluto y solvente. Aún no es del todo preciso. Al terminar de dispensar el líquido se activa una funci
* motor_paso_paso:
Por medio de la consola le pide al usuario que indique la cantidad de pasos que el motor debe dar.
