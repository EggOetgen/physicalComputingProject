

//https://www.instructables.com/id/How-to-access-5-buttons-through-1-Arduino-input/
int potOnePin = 0;
int potTwoPin = 1;

int tempoPotPin = 2;

//LEDpins
int ledOne = 9;
int ledTwo = 8;
int ledThree = 7;
int ledFour = 6;
int ledFive = 5;
int ledSix = 4;
int ledSeven = 3;
int ledEight = 2;

int randoSwitch = 12;

//sequencer switches pinn
int switchAnalogPin = 5;

int backAndForthSwitch = 13;
bool backAndForth;

int selector = 0;
int pitchPin = 10;    // LED connected to digital pin 9
int modPin =11;
float notes[] ={0, 1, 4, 2, 10, 8, 20, 10};
float mods[] ={0, 0, 0, 0, 0, 0, 0, 0};

//int leds[] = {ledOne, ledTwo, ledThree, ledFour, ledFive, ledSix, ledSeven, ledEight};
int leds[] = {9,8,7,6,5,4,3,2};
int i;
int incrementor;
int tempo;
void setup() {
  pinMode(modPin, OUTPUT);
  pinMode(pitchPin, OUTPUT);
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
   pinMode(ledThree, OUTPUT);
   pinMode(ledFour, OUTPUT); 
    pinMode(ledFive, OUTPUT);
    pinMode(ledSix, OUTPUT);
    pinMode(ledSeven, OUTPUT);
    pinMode(ledEight, OUTPUT);
   
   Serial.begin(9600);   
  i  =0;
  incrementor = 1;
  tempo = 116;
  
  backAndForth = false;
  // nothing happens in setup
}

void loop() {

int analogSwitchDiscard = analogRead(switchAnalogPin); //http://forum.arduino.cc/index.php?topic=69675.0
int analogSwitchVal = analogRead(switchAnalogPin);
if( analogRead(switchAnalogPin) ==1023){
  selector = 1;
}
else if(analogSwitchVal <1023 && analogSwitchVal > 1020 ){
  selector = 2;
}
else if(analogSwitchVal <1020 && analogSwitchVal > 1016 ){
  selector = 3;
}
else if(analogSwitchVal <1015 && analogSwitchVal > 1012 ){
  selector = 4;
}
else if(analogSwitchVal <979 && analogSwitchVal > 975 ){
  selector = 5;
}
else if(analogSwitchVal <932 && analogSwitchVal > 928){
  selector = 6;
}
else if(analogSwitchVal <900 && analogSwitchVal > 400 ){
  selector = 7;
}
else if(analogSwitchVal <200 && analogSwitchVal > 50 ){
  selector = 8;
}
else selector = 0;

int analogPitchPotDiscard = analogRead(potOnePin);
int analogPitchPotVal = analogRead(potOnePin);

int analogModPotDiscard = analogRead(potTwoPin);
int analogModPotVal = analogRead(potTwoPin);

analogPitchPotVal = map(analogPitchPotVal, 0, 1023, 0, 100);
analogModPotVal = map(analogModPotVal, 0, 1023, 0, 55);

if(selector ==1){
  notes[0] = analogPitchPotVal;
  mods[0] = analogModPotVal;
  i = 0;
}
if(selector ==2){
  notes[1] = analogPitchPotVal;
  mods[1] = analogModPotVal;
  i=1;
}
if(selector ==3){
  notes[2] = analogPitchPotVal;
  mods[2] = analogModPotVal;
  i=2;
}
if(selector ==4){
  notes[3] = analogPitchPotVal;
  mods[3] = analogModPotVal;
  i=3;
}
if(selector ==5){
  notes[4] = analogPitchPotVal;
  mods[4] =analogModPotVal;
  i = 4;
}
if(selector ==6){
  notes[5] = analogPitchPotVal;
  mods[5] = analogModPotVal;
  i=5;
}
if(selector ==7){
  notes[6] = analogPitchPotVal;
  mods[6] = analogModPotVal;
  i=6;
}
if(selector ==8){
  notes[7] = analogPitchPotVal;
  mods[7] = analogModPotVal;
  i=7;
}

int tempoDiscard = analogRead(tempoPotPin);
int tempTempo = analogRead(tempoPotPin);
tempo = map(tempTempo, 0, 1023, 1, 400);
  
if(digitalRead(randoSwitch) == HIGH){
  randomise();
  i = random(8);
  }
 analogWrite(modPin,mods[i]);
 analogWrite(pitchPin,notes[i]);//notes[i]);
 
 lights(i);
 if(digitalRead(backAndForthSwitch) ==HIGH) backAndForth = !backAndForth;
if(backAndForth == false){
 normalStep(i);
}else{
 backAndForthStep(i);
}

 delay(tempo);
 
 
}

//function for controlling the LEDs
void lights(int curr){
  for(int i = 0; i < 8; i++){
    digitalWrite(leds[i], LOW);
  }
  digitalWrite(leds[curr],HIGH);
}

//functiong for randomising values
void randomise(){

  for(int i = 0; i < 8; i++){
    notes[i] = random(100);
    mods[i] = random(50);
    
    }

  }

void normalStep(int playHead){

  playHead= (playHead+1)%8;
  i = playHead;
  }

void backAndForthStep(int playHead){
  
  
  if (playHead == 0) incrementor = 1;
  if (playHead == 7) incrementor = -1;
  playHead += incrementor;

i = playHead;
  }
