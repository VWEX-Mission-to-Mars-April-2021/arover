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

void turnAngle(int angle){//angle should be between 0 and 360
      int counts = round((float)85/90 * (int)angle);
      leftcounter = 0;
      halt(0);

    while (leftcounter <= counts){
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
  reverse(1000);
  turnright(2000);
  reverse(1000);
  turnleft(2000);
}

//Light sensed from centre sensor
int lightSensed(){
  return analogRead(CENTRE_LDR);
}

//forward snake motion
void snakey(){
  forward(1000);
  turnright(2000);
  forward(1000);
  turnleft(2000);
}

void loop(){//main routine
  count++;
  if (count == 1) {//snakey motion on count 1
    rsnakey();
    turnAngle(180);
    snakey();
    turnAngle(180);
  }
  else if(count == 2){//search for light intensity
      int lightLevels[8];
      for(int i=0;i<8;i++){//rotate 45 degree, measure light, repeat 7 more times
        lightLevels[i] = lightSensed();
        turnAngle(45);
      }
      int turnsNeeded = 0;
      int highestLevel = 0;

      for (int i = 0; i < 8; i++) {//determins highest light intensity measured
        int level = lightLevels[i];
      
        if (level > highestLevel) {
          highestLevel = level;
          turnsNeeded = i;//finds no of 45 degree turns required
        }
      }  
        //code to rotate 
        turnAngle(turnsNeeded * 45);
      forward(1000);
  }
  else if(count == 3 ){
  
    for (int i = 0; i < 10; i++){
      {
        int num = random(1, 3);
        if (num == 1) {
          //Turn random angle
          int angle = random(1,360);
          turnAngle(angle);
        } else if (num == 2) {
          //Reverse for 2 seconds?
          reverse(2000);
          halt(0);
        } else {
          //Forward 1 sec? 
          forward(1000);
          halt(0);
        }
      }
    }
  }
}
