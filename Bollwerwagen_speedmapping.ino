/*
Author: Marcel Thekook
License: Free to use (Also in comerical use) (mentioning would be nice)

Definition of Wires for controlling Purpose:
#define BatteriePlus(+24V) 1
#define Rückwärts 2
#define Vorwärts 3
#define Hupe(+24V) 4 
#define Rot(Gashebel) 7
#define Schwarz(Gashebel) 8
#define Grün(Gashebel) 9
#define Hupe (GND) 5
#define Batterie(GND) 5
Die anderen Kabel sollten nicht in Verwendung sein. Bitte Angaben Prüfen, Code kann veraltet sein
*/

/*
Preconditions:
Verwendet wird ein Digital zu Analog converter, der per I2C angesprochen wird.
Model: 
DS 18030-010	Digitalpoti, 2-Kanal, 256 Schritte, 10 kOhm, DIL-16	2	15,36 €
(12,90 €  netto)
MCP 4151-103E/P	Digitalpoti, 1-Kanal, 257 Schritte, 10 kOhm, DIP-8	2	2,60 €
(2,18 €  netto)
Reichelt
Für weiteres Marcel fragen.
*/

#include <Wire.h>

#define input_gas A0    // Eingang Daumengas
#define output_led 13   // Info LED
#define output_relai 5  // Output Relai zur Gasabschaltung

//Variablen
int sv1 = 0;
int sv1_buffer = 0;
int sv1low = 174;
int sv1high = 922;

int reslow = 0;
int reshigh = 128;

byte val_speed = 0;

bool enabled = true;
 
void setup() {
  Serial.begin(9600);
  pinMode(output_led, OUTPUT);
  pinMode(output_relai, OUTPUT);
  Wire.begin();
  digitalWrite(output_led, HIGH);

  sv1 = analogRead(input_gas);
  val_speed = map(sv1, sv1low, sv1high, reslow, reshigh);
  writeSpeed();
}

void loop() {
  /*
    sv1 = analogRead(input_gas);
    if (sv1 == sv1_buffer){
    }else{
      val_speed = map(sv1, sv1low, sv1high, reslow, reshigh);
      writeSpeed();  
    }
    */
    sv1 = analogRead(input_gas);
    sv1_buffer = sv1;
    Serial.println("Input Gas:");
    Serial.println(sv1);
    Serial.println("Speed Value");
    Serial.println(val_speed);
    delay(500);

    val_speed = map(sv1, sv1low, sv1high, reslow, reshigh);

    Wire.beginTransmission(0x28); // transmit to device 0x28)
    Wire.write(0xAA);            // sends instruction byte,
    Wire.write(val_speed);             // sends potentiometer value byte
    Wire.endTransmission();     // stop transmitting
    
}

void writeSpeed(){
  if(enabled){
    Wire.beginTransmission(0x28); // transmit to device 0x28)
    Wire.write(0xAA);            // sends instruction byte,
    Wire.write(val_speed);             // sends potentiometer value byte
    Wire.endTransmission();     // stop transmitting
    }
  }
