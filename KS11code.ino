//This is Line follower robot code.
#include "CytronMotorDriver.h"

int IRL = A0;
int IRR = A1;
int Sig1 = 7; // this pin is use to communicate with other ESP32 borad
int Sig2 = 8;
CytronMD motor1(PWM_DIR, 3, 2);  // PWM 1 = Pin 3, DIR 1 = Pin 2.
CytronMD motor2(PWM_DIR, 5, 4); // PWM 2 = Pin 5, DIR 2 = Pin 4.


void setup()
{
  pinMode(IRL,INPUT);
  pinMode(IRR,INPUT);
  pinMode(Sig1,INPUT);
  pinMode(Sig2,INPUT);
  Serial.begin(9600);
  
}
void loop()
{
  int L=analogRead(IRL);
  int R=analogRead(IRR); // black = 1 , green = 0
  int S1=digitalRead(Sig1);
  int S2=digitalRead(Sig2);
  Serial.println("-------------------------------------------------");
  Serial.print("Left = ");
  Serial.println(L);
  Serial.print("Right = ");
  Serial.println(R);
  Serial.println("-------------------------------------------------");


 if   (S1==1 && S2 ==1) 
  {
    if      (L < 500 && R < 500)
    {
      Forward();
    }
      else if (L > 500 && R < 500) // ;ซ้ายดำแล้วเลี้ยวซ้าย
    {
      Left();
    }
      else if (L < 500 && R > 500)
    {
      Right();
    }
      else Stop();
  }
  else if (S1==0 && S2 ==0)
  {
    Stop();
  }
  else if (S1==0 && S2 ==1)
  {
    WiggleR();
  }
  else if (S1==1 && S2 ==0)
  {
    WiggleL();
  }
  else {Stop();}
}

void Forward()
{
  motor1.setSpeed(120); // -255 to 255 for the range of speed negative mean backward
  motor2.setSpeed(120);
}

void Left()
{
  motor1.setSpeed(-20);
  motor2.setSpeed(160);
}

void Right()
{
  motor1.setSpeed(160);
  motor2.setSpeed(-20);
}

void Stop()
{
  motor1.setSpeed(0);
  motor2.setSpeed(0);
}

void WiggleR()
{
  motor1.setSpeed(240);
  motor2.setSpeed(0);
  delay(100);
  motor1.setSpeed(0);
  motor2.setSpeed(240);
}


void WiggleL()
{
  motor1.setSpeed(0);
  motor2.setSpeed(240);
  delay(100);
  motor1.setSpeed(240);
  motor2.setSpeed(0);
}
