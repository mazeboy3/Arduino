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

void trimGas(){
  
}