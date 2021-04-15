ReturnedTrue
#8774
Drinking tea



arover
Search


Liam — Yesterday at 14:33
did u guys pass the straight line challenge?

Oskar W — Yesterday at 14:33
yea

Liam — Yesterday at 14:33
nice!

Katy — Yesterday at 14:36
Their repo is not very organised...(edited)


Oskar W — Yesterday at 14:37
wait we can see theirs!?

Katy — Yesterday at 14:37
yes

Rastr — Yesterday at 14:37
i think so

Katy — Yesterday at 14:37
that is what I have been doing lol

Oskar W — Yesterday at 14:37
also i approve of the dark mode

Rastr — Yesterday at 14:37
so can we see their rover in action ?!

Liam — Yesterday at 14:37
light mode attracts bugs 

SpoookiBoi (Andy) — Yesterday at 14:41

Katy — Yesterday at 15:15
@astrotutor our code for story 7 is ready to be tested
[15:18]
Helios are still on story 6 but the third team is also on story 7

Oskar W — Yesterday at 15:18
oki

Rastr — Yesterday at 15:19
yay

Oskar W — Yesterday at 15:19
so much for that meme
[15:20]
more memes : )


Will — Yesterday at 15:30
@astrotutor We're ready to test for story 7 again

Katy — Yesterday at 15:33
looks like we are going to have to wait for Helios's team maybe we should start 8?

Rastr — Yesterday at 15:34
idk if something goes wrong with story 7 we will have to back track

Katy — Yesterday at 15:34
ok

Rastr — Yesterday at 15:35
i don't mind doing it though like reading through it

Liam — Yesterday at 15:35
7 & 8 are fairly similar

Will — Yesterday at 15:37
Looks like we need an accurate 90 degrees anywho
15 April 2021

Rastr — Today at 10:02
@astrotutor we just need to check the code for story seven

Rastr — Today at 10:12
int fwdright = 12;
int fwdleft = 8;
int revright = 11;
int revleft = 7;
int enableleft = 9;
int enableright = 10;
Expand
message.txt
3 KB
[10:14]
will has tinker cad loaded for you yet?

Will — Today at 10:18
We could do something like:
while (leftcounter <= 90 && count < 4) {

Katy — Today at 10:24
while we wait i am going to read through the avoiding obstacles section in the guide we will need for story 9

Rastr — Today at 10:25
yeah that's a good idea tell us what its about when you finish reading about it(edited)

Oskar W — Today at 10:25
ill give it a look too

Katy — Today at 10:26
We will need to install the NewPing library
[10:26]
we may need to use the arduino ide instead since tinker cad does not use this library

Oskar W — Today at 10:27
we have task 8 to do before that anyway so wr're good for now i think

Will — Today at 10:27
I'll try and install it

Katy — Today at 10:27
okay

Will — Today at 10:27
I think he said to skip story 8

Liam — Today at 10:27
skip 8

1

Rastr — Today at 10:27
i think they said to skip task 8 as it is similar to task 7

Oskar W — Today at 10:27
oh ok

Liam — Today at 10:27
cuz its basically the same as 7 and there isnt a lot of time left

Rastr — Today at 10:31
is team helios on story 9

Oskar W — Today at 10:31
think teyre testing 7

Rastr — Today at 10:31
oh

Katy — Today at 10:32
looks like the third team are also on story 7(edited)

Rastr — Today at 10:32
oh

Oskar W — Today at 10:33
we're only behind cuz of the small error, plus its not a problem

Will — Today at 10:36
Like so?
  if (count <= 4) {  

Rastr — Today at 10:36
yes

Rastr — Today at 10:49
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
int count = 0;

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
  if (count <= 3) {  
    forward(0);
    //when count is 2 the rover needs to go twice as far 
    if (leftcounter == 150) {
      halt(0);
      leftcounter = 0;
      count++;
      

      //Turn 90 degrees
      while (leftcounter <= 90) {
        digitalWrite(enableleft,HIGH);
        digitalWrite(enableright,HIGH);
        digitalWrite(fwdleft,LOW);
        digitalWrite(fwdright,HIGH);

... (19 lines left)
Collapse
message.txt
3 KB

Message #arover
﻿



ONLINE — 11

astrotutor

Elliot

Katy

laylabb

LeonH

Creating my meme collection

Liam

Oskar W

Rastr

Samuel Warner

SpoookiBoi (Andy)

Sniper I Monkey P

Will

Drinking tea
OFFLINE — 6

Alex Green

Bxnjohnson

itz_me_jordzz

ofbeatobject8

speakersforschools

ZakGarside
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
int count = 0;

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
  if (count <= 3) {  
    forward(0);
    //when count is 2 the rover needs to go twice as far 
    if (leftcounter == 150) {
      halt(0);
      leftcounter = 0;
      count++;
      
      //Turn 85 degrees
      while (leftcounter <= 85) {
        digitalWrite(enableleft,HIGH);
        digitalWrite(enableright,HIGH);
        digitalWrite(fwdleft,LOW);
        digitalWrite(fwdright,HIGH);

        digitalWrite(revright,LOW);
        digitalWrite(revleft,HIGH);
      }

      leftcounter = 0;
    }
  } else{ 
    halt(20000);
  }
}

//Increment left and right counters
void lefttracker(){
  leftcounter++;
}

void righttracker(){
  rightcounter++; 
}
