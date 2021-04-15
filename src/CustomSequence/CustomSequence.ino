#include <NewPing.h>

int fwdright = 12;
int fwdleft = 8;
int revright = 11;
int revleft = 7;
int enableleft = 9;
int enableright = 10;
const int leftfeedback = 2;//Switch pins
const int rightfeedback = 3;
volatile int leftcounter = 0;
volatile int rightcounter = 0;
int speedLeft = 200;
int count = 0;

  
//left, centre and right light sensors
const int LEFT_LDR = A7;
const int CENTRE_LDR = A6;
const int RIGHT_LDR = A2;


#define TRIGGER 4 //tigger
#define ECHO 5 //echo

int maxdistance = 200; // Maximum distance we want to ping for (in centimeters).
NewPing sonar(TRIGGER, ECHO, maxdistance);

//Array of pins
int vars[6] = {fwdright,fwdleft,revright,revleft,enableleft,enableright};

void setup() 
{
  //Set up all pins
  for(int v : vars){
    pinMode(v,OUTPUT);
     
  }
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(leftfeedback), lefttracker, RISING);
  attachInterrupt(digitalPinToInterrupt(rightfeedback), righttracker, RISING);

  digitalWrite(enableleft,HIGH);
  digitalWrite(enableright,HIGH);
  
  analogWrite(enableleft, 150);
  analogWrite(enableright, 150);
  
  pinMode(LEFT_LDR, INPUT);
  pinMode(CENTRE_LDR, INPUT);
  pinMode(RIGHT_LDR, INPUT);
  
  sonar.ping_cm();
}

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

void turnright(int mSeconds) {
  analogWrite(enableleft, 255);
  analogWrite(enableright, 120);
  delay(mSeconds);
}

void turnleft(int mSeconds)  {
  analogWrite(enableright, 255);
  analogWrite(enableleft, 120);
  delay(mSeconds);
}
void lefttracker(){
  leftcounter++;
}

void righttracker(){
  rightcounter++; 
}
// Turn left by 180 degrees
void turnLeft180() {
  leftcounter = 0;
  halt(0);

  while (leftcounter <= 170){
    digitalWrite(enableleft, HIGH);
    digitalWrite(enableright, HIGH);
    
    digitalWrite(fwdleft, LOW);
    digitalWrite(fwdright, HIGH);
    
    digitalWrite(revleft, HIGH);    
    digitalWrite(revright, LOW);
  }

  leftcounter = 0;
}


//Detect obstacles
bool obstacle_in_path(){
  int distance = sonar.ping_cm();
  return distance <= 12; //If there is an obstacle 12cm or less ahead
}

//reverse snake motion
void rsnakey(){
  reverse(2000);
  turnright(1000);
  reverse(2000);
  turnleft(1000);
}

//Light sensed from centre sensor
int lightSensed(){
  return analogRead(CENTRE_LDR);
}

//forward snake motion
void snakey(){
  forward(2000);
  turnright(1000);
  forward(2000);
  turnleft(1000);
}

void loop(){//main routine
//counter++;
//if (counter % 2 == 1) {
  rsnakey();
  turnLeft180();
  snakey();
  turnLeft180();
//}
//else if(counter % 2 == 0){
    
  //}
  
  
}
