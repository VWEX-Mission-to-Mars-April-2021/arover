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

}

void halt(){ //stopps rover advance

  digitalWrite(fwdleft,LOW);
  digitalWrite(fwdright,LOW);
  digitalWrite(revleft,LOW);
  digitalWrite(revright,LOW);

}

void reverse(int mSeconds){ //stop motor forward, rover reverses

  digitalWrite(fwdleft,LOW);
  digitalWrite(fwdright,LOW);
  digitalWrite(revleft,HIGH);
  digitalWrite(revright,HIGH);
  delay(mSeconds);

}

void forward() {//stop motor reverse, rover forward

  digitalWrite(revleft,LOW);
  digitalWrite(revright,LOW);
  digitalWrite(fwdleft,HIGH);
  digitalWrite(fwdright,HIGH);

}


void loop(){
  forward();

  Serial.println("Left Counter ");
  Serial.println(leftcounter); // This is printing then a new Line after
  Serial.println("Right Counter ");
  Serial.println(rightcounter);

  //If the rover has travelled 2m stop for 20 seconds
  if(leftcounter >= 870){
    Serial.println("Reached 2 meters ");
    halt();
    delay(20000);
  }

}

void lefttracker(){
  leftcounter++;
}

void righttracker(){
  rightcounter++; 
}
