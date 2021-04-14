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

//Array of pins
int vars[6] = {fwdright,fwdleft,revright,revleft,enableleft,enableright};

void setup() 
{
  //Set up all pins
  for(int v : vars){
    pinMode(v,OUTPUT);
     
  }
  
  analogWrite(enableleft, 150);
  analogWrite(enableright, 150);
  
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
  
  // digitalWrite(revleft,LOW);
  // digitalWrite(revright,LOW);
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


void loop(){
  forward(2000);
  turnright(1000);
  forward(2000);
  turnleft(1000);
  forward(2000);
  turnright(1000);
  forward(2000);
  turnleft(1000);
  forward(2000);
  turnright(1000);
  forward(2000);
  turnleft(1000);
  forward(2000);
  turnright(1000);
  halt(20000);
}
