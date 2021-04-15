#include <NewPing.h>

int fwdright = 12;
int fwdleft = 8;
int revright = 11;
int revleft = 7;
int enableleft = 9;
int enableright = 10;
//Array of pins
int vars[6] = {fwdright,fwdleft,revright,revleft,enableleft,enableright};

const int leftfeedback = 2;//Switch pins
const int rightfeedback = 3;
volatile int leftcounter = 0;
volatile int rightcounter = 0;
const int reduc = 50;
int count = 0;


const int startspeed = 150;
int leftspeed; 
int rightspeed;

const int TRIGGER_DOWN = 13;
const int ECHO_DOWN = 17;
const int MAX_DISTANCE = 200; // Maximum distance we want to ping for (in centimeters).

NewPing sonar(TRIGGER_DOWN, ECHO_DOWN, MAX_DISTANCE);

void halt(int mSeconds){ //stopps rover advance
  
  digitalWrite(fwdleft,LOW);
  digitalWrite(fwdright,LOW);
  digitalWrite(revleft,LOW);
  digitalWrite(revright,LOW);
  delay(mSeconds);
}

void reverse(int mSeconds){ //stop motor forward, rover reverses
  
  digitalWrite(fwdleft,LOW);
  digitalWrite(fwdright,LOW);
  digitalWrite(revleft,HIGH);
  digitalWrite(revright,HIGH);
  delay(mSeconds);
}

void forward(int mSeconds) {//stop motor reverse, rover forward
  
  digitalWrite(revleft,LOW);
  digitalWrite(revright,LOW);
  digitalWrite(fwdleft,HIGH);
  digitalWrite(fwdright,HIGH);
  delay(mSeconds);
  
}

void turnright(int mSeconds) {//right turn by motor speed change
  analogWrite(enableleft, 255);
  analogWrite(enableright, 120);
  delay(mSeconds);
}

void turnleft(int mSeconds)  {//left turn by motor speed change
  analogWrite(enableright, 255);
  analogWrite(enableleft, 120);
  delay(mSeconds);
}

void updateSpeeds(){
  analogWrite(enableleft,rightspeed);
    analogWrite(enableright,leftspeed);
}

void setup() {
  for(int v : vars){
    pinMode(v,OUTPUT);
  }
  
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(leftfeedback), lefttracker, RISING);
  attachInterrupt(digitalPinToInterrupt(rightfeedback), righttracker, RISING);
  
  leftspeed = startspeed;
  rightspeed = startspeed;
  
  analogWrite(enableleft, rightspeed);
  analogWrite(enableright, leftspeed); 
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  sonar.ping_cm();
}

void setHigh(int pin) {
  digitalWrite(pin, HIGH);
}

void setLow(int pin) {
  digitalWrite(pin, LOW);
}

/*void turnLeft90() {
  leftcounter = 0;

  while (leftcounter <= 85) {
    setHigh(enableleft);
    setHigh(enableright);
    
    setLow(fwdleft);
    setHigh(fwdright);
    
    setHigh(revleft);    
    setLow(revright);
  }

  leftcounter = 0;
}*/

//Return true if there is an obstacle in the path
bool objectBelow(){
  int distance = sonar.ping_cm();
  return distance <= 12; //If there is an obstacle 12cm or less ahead
}

void loop() {
 forward(0);
 if(!objectBelow()){
    halt(1000);
    reverse(1000);
    halt(20000);
  }
  
  delay(50);
}
//Increment left and right counters
void lefttracker(){
  leftcounter++;
}

void righttracker(){
  rightcounter++; 
}
