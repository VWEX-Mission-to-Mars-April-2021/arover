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
const int reduc = 50;

const int startspeed = 150;
int leftspeed; 
int rightspeed;

  
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
  
  leftspeed = startspeed;
  rightspeed = startspeed;

  
  analogWrite(enableleft, rightspeed);
  analogWrite(enableright, leftspeed); 
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

void loop(){
  //10 seconds has passed whilst travelling
  if(millis() >= 10000){
    halt(0);
  }
  else{ //If 10 seconds have not passed yet

    forward(0);
    //Check if counters are equal
    if(leftcounter != rightcounter){
      if(leftcounter < rightcounter){
      // leftenable should increase
        leftspeed += 20;
        rightspeed -= 20;
        forward(0);
        updateSpeeds();
      }
      else if(rightcounter < leftcounter){
      // right enable should increase
        leftspeed -= 20;
        rightspeed += 20;
        forward(0);
        updateSpeeds();
      }
    }
    else {
      forward(0);
      leftspeed = 150;
      rightspeed = 150;
      updateSpeeds();
     }  
   }
}

//Increment left and right counters
void lefttracker(){
  leftcounter++;
}

void righttracker(){
  rightcounter++; 
}
