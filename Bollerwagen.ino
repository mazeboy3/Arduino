/* ToDos:
 *  Interrupt für die Bremse
 *  Kein direkter wechsel von vorwärts auf Rückwärts
 *
 *
 *
 */



// Geschwindigkeiten
const int speedAdjustIn = A0;
const int speedInput = A1;      // Geschwindigkeitseingang vom Daumengas
const int speedOutputL =  3;    // Geschwindigkeitsausgang zu Controller 1 (Fahrtrichtung Links)
const int speedOutputR = 4;     // Geschwindigkeitsausgang zu Controller 2 (Fahrtrichtung Rechts)

//Abschaltungen
const int bremse = 5;           //Eingang für betätigen der Bremse
const int kippAbschaltung = 6;  //Kippabschaltung bei überschrittenem Neigungswinkel

//Fahrmodus
const int entriegelung = 7;     //Schaltet die Elektromotoren Frei --> Später Schlüsselinstallation
const int fahrmodus = 8;        //Fahrmodus Reedkontakt zur Freischaltung der vollen Geschwindigkeit
const int richtung = 9;         //Vorwärts oder Rückwärtsbetrieb


/*
//Fahrsicherheit
const int blinker
const int bremslicht
const int Warnblinklicht

*/

//Arbeitsvariablen
int varSpeed = 0;
bool varModus = true; //True - Normalsmodus - False freigeschaltet
bool varRichtung = true;  //True vorwärts - False rückwärts
bool gearBuffer = true;

enum direction{
  right,
  left,
  warn
}


void setup() {
  pinMode(speedOutputL, OUTPUT);
  pinMode(speedOutputR, OUTPUT);
  pinMode(kippAbschaltung, INPUT);
  pinMode(entriegelung, INPUT);
  pinMode(fahrmodus, INPUT);
  pinMode(richtung, INPUT);

  pinMode(bremse, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(bremse), interrupt, CHANGE);
}

void loop() {

  if(digitalRead(entriegelung)){  //sofern die Entriegelung aktiviert ist, starte mit dem Programm
    varModus = digitalRead(fahrmodus); //ToDo prüfen ob so möglich
    varRichtung = digitalRead(richtung);
     if(!bremse && !kippAbschaltung){
        varSpeed = map(analogRead(speedInput), 0, 255, 0, speedadj());
      }
    }
}

void interrupt() {

  }

int speedadj(){
  return (analogRead(speedAdjustIn));
}

void wheelControl(bool mode, bool gear){
  if (!gearBuffer == gear) {delay(3000); gearBuffer = gear;}
  if (gear){
    digitalWrite(richtung, LOW);
  }else{
    digitalW
  }

  if (mode == true) {
    varSpeed = map(analogRead(speedInput), 0, 255, 0, speedadj());
  }else{varSpeed = analogRead(speedInput);}

}

void lighting(){

}

void blink(direction d){

}

void zapfLicht(){

}