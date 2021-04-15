#include <NewPing.h>

// Pin definitions
int fwdright = 12;
int fwdleft = 8;
int revright = 11;
int revleft = 7;
int enableleft = 9;
int enableright = 10;

// Array of pins
int vars[6] = {fwdright,fwdleft,revright,revleft,enableleft,enableright};

const int leftfeedback = 2; // Switch pins
const int rightfeedback = 3;

volatile int leftcounter = 0;
volatile int rightcounter = 0;

const int startspeed = 150;
int leftspeed = startspeed; 
int rightspeed = startspeed;

const int TRIGGER_DOWN = 13;
const int ECHO_DOWN = 17;
const int MAX_DISTANCE = 200; // Maximum distance we want to ping for (in centimeters).

NewPing sonar(TRIGGER_DOWN, ECHO_DOWN, MAX_DISTANCE);

void setHigh(int pin) {
  digitalWrite(pin, HIGH);
}

void setLow(int pin) {
  digitalWrite(pin, LOW);
}

void halt(int mseconds) { // Stops rover advance
  setLow(fwdleft);
  setLow(fwdright);
  
  setLow(revleft);
  setLow(revright);
  
  delay(mseconds);
}

void reverse(int mseconds) { // Stop motor forward, rover reverses
  setLow(fwdleft);
  setLow(fwdright);

  setHigh(revleft);
  setHigh(revright);
  
  delay(mseconds);
}

void forward(int mseconds) { // Stop motor reverse, rover forward
  setLow(revleft);
  setLow(revright);
  
  setHigh(fwdleft);
  setHigh(fwdright);
  
  delay(mseconds);
  
}

void turnLeft(int mseconds)  { // Left turn by motor speed change
  analogWrite(enableright, 255);
  analogWrite(enableleft, 120);
  
  delay(mseconds);
}

void turnRight(int mseconds) { // Right turn by motor speed change
  analogWrite(enableleft, 255);
  analogWrite(enableright, 120);
  
  delay(mseconds);
}

void updateSpeeds() {
  analogWrite(enableleft, rightspeed);
  analogWrite(enableright, leftspeed);
}

// Increment left and right counters
void leftTracker() {
  leftcounter++;
}

void rightTracker() {
  rightcounter++; 
}

void setup() {
  for(int v : vars){
    pinMode(v, OUTPUT);
  }
  
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
  attachInterrupt(
    digitalPinToInterrupt(leftfeedback), 
    leftTracker, 
    RISING
  );
   
  attachInterrupt(
    digitalPinToInterrupt(rightfeedback), 
    rightTracker, 
    RISING
  );
  
  updateSpeeds();
  sonar.ping_cm();
}

// Return true if there is an obstacle in the path
bool objectBelow() {
  int distance = sonar.ping_cm();
  
  return distance <= 12; // If there is an obstacle 12cm or less ahead
}

void loop() {
 forward(0);
 
 if(!objectBelow()) {
    halt(1000);
    reverse(1000);
    halt(20000);
  }
  
  delay(50);
}
