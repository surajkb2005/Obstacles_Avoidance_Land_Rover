#include<Servo.h>


int echopin = 10;
int triggerpin = 8;
long duration;
int distance;


int servopin = 11;
Servo myservo;


int leftvalue,rightvalue,frontvalue;
int in1=2,in2=3,in3=4,in4=5;


int red = 7;
int green = 6;


void setup() {
  pinMode(triggerpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
  myservo.attach(servopin);


  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);


  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);


  Serial.begin(9600);


  //initially set the servomotor towards forward
  servomotor(90);
  frontvalue = countDistance();
  delay(1000);//start after 1 sec


  //start motor forward
  forward();
}
int countDistance()
{
  digitalWrite(triggerpin,LOW);
  delayMicroseconds(2);


  digitalWrite(triggerpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin,LOW);


  duration = pulseIn(echopin,HIGH);
  distance = duration * 0.0343/2;  //distance = time*speed_of_sound/2
  //Serial.println(distance);
  //delay(500);
  return distance;
}
void checkLeft()
{
  servomotor(180);               //turn the sensor to left
  delay(150);                    //wait for motor to turn
  leftvalue = countDistance(); //count the left distance
  delay(150);
  servomotor(90);              //set servo motor default
  delay(150);                  //wait for half second
}
void checkRight()
{
  servomotor(0);               //turn the sensor to right
  delay(150);                     //wait for motor to turn
  rightvalue = countDistance(); //count the right distance
  delay(150);
  servomotor(90);           //set servo motor to default
  delay(150);                  //wait for half second
}
void servomotor(int value)
{
  myservo.write(value);
}




void forward()
{
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);


  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void stop()
{
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);


  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void leftturn()
{
  back(200);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(500);
  stop();
}
void rightturn()
{
  back(200);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(500);
  stop();
}
void back(int time)
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(time);
  stop();
}




void loop() {
  //initial
  //servomotor(90);
  frontvalue = countDistance();


  Serial.println("motor started to move front");


  if(frontvalue<25 && frontvalue>0)
  {
      //stop motor
      stop();
      Serial.println("motor stopped to move front");


      checkLeft();
      checkRight();


      if(leftvalue>25 && rightvalue>25)  //choose best value
      {
        if(leftvalue>rightvalue)
        {
          //turn left
          leftturn();
          Serial.println("left turn done");
        }
        else
        {
          //turn right
          rightturn();
          Serial.println("right turn done");
        }
      }
      else if(leftvalue>25)
      {
        //turn left
        leftturn();
        Serial.println("left turn done");
      }
      else if(rightvalue>25)
      {
        //turn right
        rightturn();
        Serial.println("right turn done");
      }
      else
      {
        //reverse and U-turn
        back(500);
        rightturn();
        Serial.println("U-turn done");                        
      }
      //delay(250);                             //wait 0.25sec till turning
      //start motor
      forward();
      Serial.println("motor started to move front after turn");
  }
  else
  {
    forward();
  }
  delay(100);
}



