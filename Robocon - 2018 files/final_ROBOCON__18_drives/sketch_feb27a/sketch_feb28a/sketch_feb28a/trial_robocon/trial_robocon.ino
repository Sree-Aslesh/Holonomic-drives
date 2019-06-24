#include<Timer.h>
Timer t;
int lightpin=40;
float Kp = 0.75;
//const int Ki = 0;
int idlepin = 33;
int abb = 40;
float abc = 45;
float Kd = 0.35;
float Kp1 = 0.65;
float Kd1 = 0.45;  
float setPoint = 35; 
float baseSpeed = 55;  
float maxSpeed = 150;  
float integral=0;
float lastError = 0;
float motorSpeed;
float lastError1 = 0;
float motorSpeed1;
int L1CW=14;
int L1CCW=4;
int L1PWM=3;
int L2CW=6;
int L2CCW=7;
int L2PWM=5;
int R1CW=8;
int R1CCW=11;
int R1PWM=9;
int R2CW=12;
int R2CCW=13;
int R2PWM=10;
float ls_prev=0;
float ls_for_prev=0;
float output=0;
int a[8];
int k=0;
float product=0;
float sum=0;
float ls;//check data type
float ls_for; //check data type
int junctionPulse = A3;
int junctionPulse1 = A1;
int j=0;
int i;
int b=1;
int h=0;
int c=0;

// new definitions

int ls_mid = A10;
int ls_mid_junction=41;

void straight()
{ 
  digitalWrite(L1CW,HIGH);
  digitalWrite(L1CCW,LOW);
  digitalWrite(L2CW,HIGH);
  digitalWrite(L2CCW,LOW);
  digitalWrite(R1CW,HIGH);
  digitalWrite(R1CCW,LOW);
  digitalWrite(R2CW,HIGH);
  digitalWrite(R2CCW,LOW);
  
}
void reverse()
{ 
  digitalWrite(L1CW,LOW);
  digitalWrite(L1CCW,HIGH);
  digitalWrite(L2CW,LOW);
  digitalWrite(L2CCW,HIGH);
  digitalWrite(R1CW,LOW);
  digitalWrite(R1CCW,HIGH);
  digitalWrite(R2CW,LOW);
  digitalWrite(R2CCW,HIGH);
  
}
void right()
{
  digitalWrite(L1CW,HIGH);
  digitalWrite(L1CCW,LOW);
  digitalWrite(L2CW,HIGH);
  digitalWrite(L2CCW,LOW);
  digitalWrite(R1CW,LOW);
  digitalWrite(R1CCW,HIGH);
  digitalWrite(R2CW,LOW);
  digitalWrite(R2CCW,HIGH);
  
}
void left()
{
  digitalWrite(L1CW,LOW);
  digitalWrite(L1CCW,HIGH);
  digitalWrite(L2CW,LOW);
  digitalWrite(L2CCW,HIGH);
  digitalWrite(R1CW,HIGH);
  digitalWrite(R1CCW,LOW);
  digitalWrite(R2CW,HIGH);
  digitalWrite(R2CCW,LOW);
  
}
void wait()
{
  digitalWrite(L1CW,LOW);
  digitalWrite(L1CCW,LOW);
  digitalWrite(L2CW,LOW);
  digitalWrite(L2CCW,LOW);
  digitalWrite(R1CW,LOW);
  digitalWrite(R1CCW,LOW);
  digitalWrite(R2CW,LOW);
  digitalWrite(R2CCW,LOW);
  analogWrite(L1PWM,0);
  analogWrite(L2PWM,0);
  analogWrite(R1PWM,0);
  analogWrite(R2PWM,0);
}
void hault()
  {
  digitalWrite(L1CW,HIGH);
  digitalWrite(L1CCW,HIGH);
  digitalWrite(L2CW,HIGH);
  digitalWrite(L2CCW,HIGH);
  digitalWrite(R1CW,HIGH);
  digitalWrite(R1CCW,HIGH);
  digitalWrite(R2CW,HIGH);
  digitalWrite(R2CCW,HIGH);
  analogWrite(L1PWM,50);
  analogWrite(L2PWM,50);
  analogWrite(R1PWM,50);
  analogWrite(R2PWM,50);
  h=1;
}

void left_full()
{
  while(ls_for< 75)
  {
  left();
  analogWrite(L1PWM,abb);
  analogWrite(L2PWM,abb);
  analogWrite(R1PWM,abb);
  analogWrite(R2PWM,abb);
   ls_for=((float)analogRead(A2)/921)*70;
   // Serial.println(ls_for);
  }
  delay(400);
  while(ls_for>= 60)
 {
  left();
  analogWrite(L1PWM,abb);
  analogWrite(L2PWM,abb);
  analogWrite(R1PWM,abb);
  analogWrite(R2PWM,abb);
  ls_for=((float)analogRead(A2)/921)*70;
  // Serial.println(ls_for);
}
}


void right_full()
{
 while(ls_for< 75)
  {
  right();
  analogWrite(L1PWM,abb);
  analogWrite(L2PWM,abb);
  analogWrite(R1PWM,abb);
  analogWrite(R2PWM,abb);
  ls_for=((float)analogRead(A2)/921)*70;
  Serial.println("leaving right");
  delay(800);
  }
 while(ls_for>= 60)
 {
  right();
  analogWrite(L1PWM,abb);
  analogWrite(L2PWM,abb);
  analogWrite(R1PWM,abb);
  analogWrite(R2PWM,abb);
  ls_for=((float)analogRead(A2)/921)*70;
}
}
void straight_full()
{
  straight();
  analogWrite(L1PWM,80);
  analogWrite(L2PWM,80);
  analogWrite(R1PWM,80);
  analogWrite(R2PWM,80);
}
void light_on()
{
  digitalWrite(lightpin,LOW);
  delay(300);
    digitalWrite(lightpin,HIGH);
  delay(300);
    digitalWrite(lightpin,LOW);
  delay(300);
    digitalWrite(lightpin,HIGH);
  delay(300);
    digitalWrite(lightpin,LOW);
  delay(300);
      digitalWrite(lightpin,HIGH);
  delay(300);  
   }
void throwme_zone1()
{ 
  light_on();
  digitalWrite(idlepin,LOW);
  digitalWrite(31,LOW);
  digitalWrite(32,LOW);

   while(digitalRead(34)==0)
   {
    Serial.println("Waiting for feedback from throwing waiting in zone1");
    //wait();
    hault();
   }
   no_work();
    //delay(2000);
  h=0;
}
void throwme_zone2()
{
  light_on();
   digitalWrite(idlepin,LOW); 
  digitalWrite(31,LOW);
  digitalWrite(32,HIGH);

   while(digitalRead(34)==0)
   {
    Serial.println("Waiting for feedback from throwing");
    //wait();
    hault();
   }
    //delay(2000);
    no_work();
  h=0;
}
void throwme_zone3()
{light_on();
  digitalWrite(idlepin,LOW);
  digitalWrite(31,HIGH);
  digitalWrite(32,LOW);

   while(digitalRead(34)==0)
   {
    Serial.println("Waiting for feedback from throwing");
    //wait();
    hault();
   }
   no_work();
    //delay(2000);
  h=0;
}
void handle()
{
   digitalWrite(idlepin,LOW); 
  digitalWrite(31,HIGH);
  digitalWrite(32,HIGH);

   while(digitalRead(34)==0)
   {
    Serial.println("Waiting for feedback from throwing");
    //wait();
    hault();
   }
   delay(20);
   colour_detect();
   no_work();
   h=0;
}


void colour_detect()
{
  int ba1 =0;
  int ba2 =0;
  ba1 = 0;//digitalRead(35);
  ba2 = 0;//digitalRead(36);
  if( ba1 ==1 && ba2 == 1)
     handle();
  else
  {
    if( ba1 ==0 && ba2 == 0)
    {
      b = 1;
    }
        if( ba1 ==0 && ba2 == 1)
    {
      b = 3;
    }
        if( ba1 ==1 && ba2 == 0)
    {
      b = 6;
    }
  }   
}
void handle_1()
{
  digitalWrite(idlepin,LOW);
  digitalWrite(31,HIGH);
  digitalWrite(32,HIGH);
  Serial.println("in handleeeeeeeeeeeeeeeeeeeeeeeeeeel 111111111111111111");
   while(digitalRead(34)==0)
   {
    Serial.println("Waiting for feedback from throwing");
    //wait();
    hault();
   }
   delay(20);
   colour_detect_1();
   no_work();
   h=0;
}
void colour_detect_1()                   // raspberry pi se read karo.
{
  int ba1 =0;
  int ba2 =0;
  ba1 = 0;//digitalRead(35);
  ba2 = 0;//digitalRead(36);
  if( ba1 ==1 && ba2 == 1)
     handle_1();
}



void no_work()
{
  
  digitalWrite(idlepin,HIGH);
 
}
float read_ls()
{
  for(k=22;k<=29;k++)
  {
    a[k-22]=digitalRead(k); 
    //a[0]=digitalRead(30);
    Serial.print(a[k-22]);
  }
  
  if(a[0]==0 && a[1]==0 && a[2]==0 && a[3]==0 && a[4]==0 && a[5]==0 && a[6]==0 && a[7]==0)
  {
    Serial.println("no line");
    output=77;
    Serial.print("output  :");
    Serial.println(output);
    return output;
  }
  else 
  {
      product = (0*a[0]*10) + (1*a[1]*10) + (2*a[2]*10) +(3*a[3]*10) +(4*a[4]*10) + (5*a[5]*10) + (6*a[6]*10) + (7*a[7]*10);
      sum = a[0] + a[1] + a[2] + a[3] + a[4] + a[5] + a[6] + a[7];
      output = product / sum ;
      Serial.print("output  :");
      Serial.println(output);
      return output;
  }
}  
  
  void line_fol()
{
  if(h==0)
  {
    ls_for=((float)analogRead(A2)/921)*70;
    if (ls_for<68)
    ls_for_prev= ls_for;
    
     Serial.print("line following ");
     Serial.print(ls_for);
    // If no line is detected, stay at the position

    ls=read_ls();
    if(ls<68)
    ls_prev=ls;
        if(ls_for >= 73)
    {
       wait();
    }

  

    // Else if line detected, calculate the motor speed and apply
  else {
    float error = ls_for - setPoint;   
    //integral = integral + error
    motorSpeed =(Kp * error + Kd * (error - lastError));//+ Ki*integral;
    lastError = error;    
    //// Serial.println(motorSpeed);
    float rightMotorSpeed = baseSpeed - motorSpeed;
    float leftMotorSpeed = baseSpeed + motorSpeed;
    straight();

    // If the speed of motor exceed max speed, set the speed to max speed
    if(rightMotorSpeed > maxSpeed) rightMotorSpeed = maxSpeed;
    if(leftMotorSpeed > maxSpeed) leftMotorSpeed = maxSpeed;

    straight();
    // If the speed of motor is negative, turn polarity
    
    if(rightMotorSpeed < 0) 
              {
                rightMotorSpeed = abs(baseSpeed - motorSpeed);
                right();
              }
    if(leftMotorSpeed < 0)
    {
      leftMotorSpeed = abs(baseSpeed + motorSpeed);
      left();
    }
    leftMotorSpeed=constrain(leftMotorSpeed,-255,255);
    rightMotorSpeed=constrain(rightMotorSpeed,-255,255);
    // Writing the motor speed value as output to hardware motor
    // Serial.println("left motor  ");
    // Serial.println(leftMotorSpeed);
    // Serial.println("right motor  ");
    // Serial.println(rightMotorSpeed);
   analogWrite(L1PWM,abs(leftMotorSpeed));
   analogWrite(L2PWM,abs(leftMotorSpeed));
   analogWrite(R1PWM,abs(rightMotorSpeed));
   analogWrite(R2PWM,abs(rightMotorSpeed));
  }
  }
}
void line_fol_back()
{
  if(h==0)
  {
    ls=read_ls();
    if(ls<68)
    ls_prev=ls;
    
    // Serial.print("line back----------- ");
    // Serial.print(ls);
    
    ls_for=((float)analogRead(A2)/921)*70;
    if (ls_for<68)
    ls_for_prev= ls_for;
    
    // If no line is detected, stay at the position
    if(ls >= 75)
    {
       wait();
    }

    // Else if line detected, calculate the motor speed and apply
  else {
      float error1 = ls - setPoint;   
      //integral = integral + error
      motorSpeed1 =(Kp1 * error1 + Kd1 * (error1 - lastError1));//+ Ki*integral;
      lastError1 = error1;    
      //// Serial.println(motorSpeed);
      float rightMotorSpeed1 = baseSpeed + motorSpeed1;
      float leftMotorSpeed1 = baseSpeed - motorSpeed1;
    reverse();

    // If the speed of motor exceed max speed, set the speed to max speed
    if(rightMotorSpeed1 > maxSpeed) rightMotorSpeed1 = maxSpeed;
    if(leftMotorSpeed1 > maxSpeed) leftMotorSpeed1 = maxSpeed;

    reverse();
    // If the speed of motor is negative, turn polarity
    
    if(rightMotorSpeed1 < 0) 
              {
                rightMotorSpeed1 = abs(baseSpeed + motorSpeed1);
                left();
              }
    if(leftMotorSpeed1 < 0)
    {
      leftMotorSpeed1 = abs(baseSpeed - motorSpeed1);
      right();
    }
    leftMotorSpeed1=constrain(leftMotorSpeed1,-255,255);
    rightMotorSpeed1=constrain(rightMotorSpeed1,-255,255);
    // Writing the motor speed value as output to hardware motor
    // Serial.println("left motor1  ");
    // Serial.println(leftMotorSpeed1);
    // Serial.println("right motor1  ");
    // Serial.println(rightMotorSpeed1);
   analogWrite(L1PWM,abs(leftMotorSpeed1));
   analogWrite(L2PWM,abs(leftMotorSpeed1));
   analogWrite(R1PWM,abs(rightMotorSpeed1));
   analogWrite(R2PWM,abs(rightMotorSpeed1));
  }
  }
}
float c1 = 0;
float c2 = 0;
float c3 = 0; 
float c0 = 0;

void stop_on_count(float abb)
{
  while((((float)analogRead(ls_mid)/921)*70)>70)
  line_fol();
  while((((float)analogRead(ls_mid)/921)*70)<30 || (((float)analogRead(ls_mid)/921)*70)>40)
  {
    if((((float)analogRead(ls_mid)/921)*70)<30)
    {
      straight();
    analogWrite(L1PWM,30);
    analogWrite(L2PWM,30);
    analogWrite(R1PWM,30);
    analogWrite(R2PWM,30);
      }
    if((((float)analogRead(ls_mid)/921)*70)>40)
    {
      reverse();
    analogWrite(L1PWM,30);
    analogWrite(L2PWM,30);
    analogWrite(R1PWM,30);
    analogWrite(R2PWM,30);
      }
    }
//  attachInterrupt(digitalPinToInterrupt(18),count1,RISING);
//  attachInterrupt(digitalPinToInterrupt(20),count2,RISING);
//  attachInterrupt(digitalPinToInterrupt(21),count3,RISING);
//  // Serial.println("stop omn count activated");
//  while(c0 < abb)
//  {
//    c0 = (c1+c2+c3)/3;
////    straight();
////    // Serial.println("value of c0");
////    // Serial.println(c0);
////    analogWrite(L1PWM,40);
////    analogWrite(L2PWM,40);
////    analogWrite(R1PWM,40);
////    analogWrite(R2PWM,40);
//    line_fol();
//  }
//  wait();
//  detachInterrupt(digitalPinToInterrupt(18));
//  detachInterrupt(digitalPinToInterrupt(20));
//  detachInterrupt(digitalPinToInterrupt(21));
//  
//  c1 =0;
//  c2 =0;
//  c3 =0;
//  c0 =0;

}
void stop_on_count_reverse(float abr)
{
//  attachInterrupt(digitalPinToInterrupt(18),count1,RISING);
//  attachInterrupt(digitalPinToInterrupt(20),count2,RISING);
//  attachInterrupt(digitalPinToInterrupt(21),count3,RISING);
//  // Serial.println("stop omn count activated");
//  while(c0 < abb)
//  {
//    c0 = (c1+c2+c3)/3;
////    reverse();
////    // Serial.println("value of c0");
////    // Serial.println(c0);
////    analogWrite(L1PWM,60);
////    analogWrite(L2PWM,60);
////    analogWrite(R1PWM,60);
////    analogWrite(R2PWM,60);
//   line_fol_back();
//  }
//  wait();
//  detachInterrupt(digitalPinToInterrupt(18));
//  detachInterrupt(digitalPinToInterrupt(20));
//  detachInterrupt(digitalPinToInterrupt(21));
//  
//  c1 =0;
//  c2 =0;
//  c3 =0;
//  c0 =0;
while((((float)analogRead(ls_mid)/921)*70)>70)
  line_fol_back();
  while((((float)analogRead(ls_mid)/921)*70)<30 || (((float)analogRead(ls_mid)/921)*70)>40)
  {
    if((((float)analogRead(ls_mid)/921)*70)<30)
    {
      straight();
    analogWrite(L1PWM,30);
    analogWrite(L2PWM,30);
    analogWrite(R1PWM,30);
    analogWrite(R2PWM,30);
      }
    if((((float)analogRead(ls_mid)/921)*70)>40)
    {
      reverse();
    analogWrite(L1PWM,30);
    analogWrite(L2PWM,30);
    analogWrite(R1PWM,30);
    analogWrite(R2PWM,30);
      }
    }
}


void count1()
{
  c1++;
}
void count2()
{
  c2++;
}
void count3()
{
  c3++;
}

void back1()
{
      
      while(j!=2)
      {
        if(digitalRead(junctionPulse1)) 
        {
            while(digitalRead(junctionPulse1)) 
            {
              Serial.println("detecting");
            }
         j++;
        }
        line_fol_back();
      }
      if(j==2)
      {
        stop_on_count_reverse(20); 
        hault();
        rotate();
        handle();
        //delay(2000);//recieving shuttlecock
        rotate();
        h=0;
}
}
void back2()
{
      while(j!=5)
      {
        if(digitalRead(junctionPulse1)) 
        {
            while(digitalRead(junctionPulse1)) 
            {
              Serial.println("detecting");
            }
         j++;
        }
        line_fol_back();
      }
      if(j==5)
      {
        stop_on_count_reverse(60);
        hault();
        rotate();
        handle();
        //delay(2000);//recieving shuttlecock
        rotate();
        h=0;
      }
}

 
void rotate()
 {
  ls_for=((float)analogRead(A2)/921)*70;
  ls=read_ls();
   Serial.println("rotating ke pehle ");
  // Serial.print("lsfor ");// Serial.println(ls_for);
  // Serial.print("lsback ");// Serial.println(ls_prev);
  while(ls_for<20 || ls <20 ||  ls>50 || ls_for>50)
  {
    // Serial.println("rotating");
    
    ls_for=((float)analogRead(A2)/921)*70;
    ls=read_ls();
    
    if(ls>73)
    ls=ls_prev;
    
    if(ls_for>73)
    ls_for=ls_for_prev;
    

    
      // Serial.print("lsfor ");// Serial.println(ls_for);
      // Serial.print("lsback ");// Serial.println(ls_prev);
  
    if(ls>=50 && ls<=70)
  {
     Serial.println("piche wala 50 se zyada");
    digitalWrite(L2CW,1);
    digitalWrite(L2CCW,0);
    digitalWrite(R2CW,0);
    digitalWrite(R2CCW,1);
    analogWrite(L1PWM,0);
   analogWrite(L2PWM,abc);
   analogWrite(R1PWM,0);
   analogWrite(R2PWM,abc);
   // rotate();
  }
        if(ls<=25 && ls>=0)
    { 
     Serial.println("piche wala 25 se kam");
    digitalWrite(L2CW,0);
    digitalWrite(L2CCW,1);
    digitalWrite(R2CW,1);
    digitalWrite(R2CCW,0);
    analogWrite(L1PWM,0);
   analogWrite(L2PWM,abc);
   analogWrite(R1PWM,0);
   analogWrite(R2PWM,abc);
   //rotate();
      }
      
    if(ls>=76)
    {
         
      if(ls_prev<20)
      {
   digitalWrite(L2CW,0);
   digitalWrite(L2CCW,1);
   digitalWrite(R2CW,1);
   digitalWrite(R2CCW,0);
   analogWrite(L1PWM,0);
   analogWrite(L2PWM,abc);
   analogWrite(R1PWM,0);
   analogWrite(R2PWM,abc);
        
        }
        if(ls_prev>50)
        {
     digitalWrite(L2CW,1);
    digitalWrite(L2CCW,0);
    digitalWrite(R2CW,0);
    digitalWrite(R2CCW,1);
    analogWrite(L1PWM,0);
   analogWrite(L2PWM,abc);
   analogWrite(R1PWM,0);
   analogWrite(R2PWM,abc);
          
         }
     //     rotate();
      }


  if(ls_for>=50 && ls_for<70)
  {
    Serial.println("aage wala 50 se zyada");
    digitalWrite(L1CW,1);
    digitalWrite(L1CCW,0);
    digitalWrite(R1CW,0);
    digitalWrite(R1CCW,1);
    analogWrite(L1PWM,abc);
    analogWrite(L2PWM,0);
    analogWrite(R1PWM,abc);
    analogWrite(R2PWM,0);
    //rotate();
    
  }
      if(ls_for<=25 && ls_for>0)
  { 
    Serial.println("aage wala 25 se kam");
    digitalWrite(L1CW,0);
    digitalWrite(L1CCW,1);
    digitalWrite(R1CW,1);
    digitalWrite(R1CCW,0);
    analogWrite(L1PWM,abc);
   analogWrite(L2PWM,0);
   analogWrite(R1PWM,abc);
   analogWrite(R2PWM,0);
   //rotate();
    
    }
    if(ls_for>=76)
    {
      
      if(ls_for_prev<20)
      {
   digitalWrite(L1CW,0);
    digitalWrite(L1CCW,1);
    digitalWrite(R1CW,1);
    digitalWrite(R1CCW,0);
    analogWrite(L1PWM,abc);
   analogWrite(L2PWM,0);
   analogWrite(R1PWM,abc);
   analogWrite(R2PWM,0);
        
        }
        if(ls_for_prev>50)
        {
     digitalWrite(L1CW,1);
    digitalWrite(L1CCW,0);
    digitalWrite(R1CW,0);
    digitalWrite(R1CCW,1);
    analogWrite(L1PWM,abc);
   analogWrite(L2PWM,0);
   analogWrite(R1PWM,abc);
   analogWrite(R2PWM,0);
          
         }
     //     rotate();
      }
    if(ls_for<=70)
    ls_for_prev=ls_for;
    if(ls<=70)
    ls_prev=ls;
  }
    analogWrite(L1PWM,0);
    analogWrite(L2PWM,0);
    analogWrite(R1PWM,0);
    analogWrite(R2PWM,0);
 }

void traversal()
 {
  // Serial.println("/////////////////////////in traversal//////////////////////////////");
  ls_for=((float)analogRead(A2)/921)*70;
  
   while(ls_for< 75)
  {
    ls_for=((float)analogRead(A2)/921)*70;
  digitalWrite(L1CW,1);
    digitalWrite(L1CCW,0);
    digitalWrite(R1CW,0);
    digitalWrite(R1CCW,1);
      digitalWrite(L2CW,0);
    digitalWrite(L2CCW,1);
    digitalWrite(R2CW,1);
    digitalWrite(R2CCW,0);
    analogWrite(L1PWM,72-15);
   analogWrite(L2PWM,72-15);
   analogWrite(R1PWM,72-15);
   analogWrite(R2PWM,55-8);
   delay(1000);
  }
 while(ls_for>= 65)
 {
  ls_for=((float)analogRead(A2)/921)*70;
  }
 
 }

void call()
{
      ls_for=((float)analogRead(A2)/921)*70;
    if (ls_for<68)
    ls_for_prev= ls_for;
    // If no line is detected, stay at the position

    ls=read_ls();
    if(ls<68)
    ls_prev=ls;
  }
void setup() {
  pinMode(A2,INPUT);
  pinMode(A1,INPUT);
  pinMode(lightpin,OUTPUT);
  digitalWrite(lightpin,HIGH);
  pinMode(junctionPulse,INPUT); 
  for(i=22;i<=30;i++)
  {
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
  for(i=2;i<=14;i++)
   {
    pinMode(i,OUTPUT);
   }
   pinMode(31,OUTPUT);
   pinMode(32,OUTPUT);
   pinMode(33,OUTPUT);
   pinMode(34,INPUT);
   digitalWrite(31,LOW);
   digitalWrite(32,LOW);
   digitalWrite(33,HIGH);
   int TickEvent = t.every(200,call);
//   line_fol();
//   while(digitalRead(junctionPulse))
//   {  
//    }
//    stop_on_count(90);
//    right_full();
//    rotate();
no_work();
line_fol();
//while(!(digitalRead(junctionPulse)))
//{
//  Serial.println("junctionpulse nahi aaya");
//  }
//   while((((float)analogRead(ls_mid)/921)*70)>73)
//   {
//   }
//while((((float)analogRead(ls_mid)/921)*70)<30 || (((float)analogRead(ls_mid)/921)*70)>40)
//  {
//    Serial.println("abhi line aaya");
//    if((((float)analogRead(ls_mid)/921)*70)<30)
//    {
//  line_fol();
//     ls_for=((float)analogRead(A2)/921)*70;
//    if (ls_for<68)
//    ls_for_prev= ls_for;
//   while(ls_for>73)
//   {
//     ls_for=((float)analogRead(A2)/921)*70;
//    if (ls_for<68)
//    ls_for_prev= ls_for;
//    }
//      }
//    if((((float)analogRead(ls_mid)/921)*70)>40)
//    {
//  line_fol_back();
//     ls_for=((float)analogRead(A2)/921)*70;
//    if (ls_for<68)
//    ls_for_prev= ls_for;
//   while(ls_for>73)
//   {
//     ls_for=((float)analogRead(A2)/921)*70;
//    if (ls_for<68)
//    ls_for_prev= ls_for;
//    }
//      }
//    }
//    wait();
//    delay(1000);
//    //rotate();
//   right();
//    analogWrite(L1PWM,60);
//   analogWrite(L2PWM,60);
//   analogWrite(R1PWM,60);
//   analogWrite(R2PWM,60);
//   delay(700);
//  while(((float)analogRead(A2)/921)*70>73)
//  {
//    }
//    
//   ls_for=((float)analogRead(A2)/921)*70;
//    if (ls_for<68)
//    ls_for_prev= ls_for;
//   while(ls_for>73)
//   {
//     ls_for=((float)analogRead(A2)/921)*70;
//    if (ls_for<68)
//    ls_for_prev= ls_for;
//    }
while((((float)analogRead(ls_mid)/921)*70)>73)
{line_fol();
}
   right();
    analogWrite(L1PWM,60);
   analogWrite(L2PWM,60);
   analogWrite(R1PWM,60);
   analogWrite(R2PWM,60);
   delay(700);
while((((float)analogRead(A2)/921)*70)>73)
{}
line_fol();
}

void loop() {

     if(digitalRead(junctionPulse)) 
        {
            while(digitalRead(junctionPulse)) 
            {
              Serial.println("detecting");
            }
         j++;
        }
 ////////////////bot starts  
  
  if (b==1 && j==1 && c==0)
  {
//    straight_full();
//    delay(200);
      stop_on_count(80);
      left_full();
      rotate();
      //stop_on_count(30);
      handle_1();     
      rotate();
      b=2;
      
  }
  
  if (b==2 && j==3 && c==0)
    {
//      straight_full();
//      delay(200);
      stop_on_count(20);
      hault();
      rotate();
      c=1;
      j=0;
      rotate();
      throwme_zone1();
      rotate();
      back1();
      //rgb read
     // b=3;
     b=1;
    }


 /////////////////////1nd zone return   
   
   if (b==1 && j==2 && c==1)
   {
      
      line_fol();//start here
      h=0;
      b=2;
   }
    if(b==2 && j==4 && c==1)
    {
      //straight_full();
      //delay(200);
       stop_on_count(108);
      hault();
      c=1;
      j=0;
      rotate();
      throwme_zone1();
      rotate();
      back1();
     //rgb read
     b=1;
   }
   if (b==3 && j==2 && c==1)
   {

      rotate();
      traversal();
      wait();
      j++;
      h=0;
      b=4;
   }
    if(b==4 && j==3 && c==1)
    {

    //left_full();
      straight_full();
      b=5;
   }
   if(b==5 && j==5 && c==1)
   {
      stop_on_count(100);
      hault();
      c=2;
      j=0;
      rotate();
      throwme_zone2();
      rotate();
      back1();
      //rgb read
      b=6;
   }  
   if (b==6 && j==2 && c==1)
   {
      //straight_full();
      //delay(100);
      right_full();
      // delay(400);
      h=0;
      b=7;
   }
    if(b==7 && j==3 && c==1)
    {
      straight_full();
      delay(200);
      left_full();
      //delay(400);
      b=8;
   }
   if(b==8 && j==8 && c==1)   //////j value doubt
   {
      straight_full();
      delay(200);
      hault();
      c=3;
      j=0;
      rotate();
      throwme_zone3();
      rotate();
      back2();
      //rgb read
      //b=3;
   }
   
 /////////////////////2nd zone return  
   if (b==1 && j==2 && c==2)
   {
      straight_full();
      delay(100);
      left_full();
      //delay(400);
      h=0;
      b=2;
   }
    if(b==2 && j==3 && c==2)
    {
      straight_full();
      delay(100);
      right_full();
      //delay(400);
      b=9;
   }
   if(b==9 && j==5 && c==2)
   {
     straight_full();
      delay(200);
      hault();
      c=1;
      j=0;
      rotate();
      throwme_zone1();
      rotate();
      back1();
      rotate();
      //rgb read
      b=6;
   }
   
   if (b==3 && j==2 && c==2)
   {
      line_fol();
      h=0;
      b=4;
   }
    if(b==4 && j==4 && c==2)
    {
//      straight_full();
//      delay(200);
      hault();
      c=2;
      j=0;
      rotate();
      throwme_zone2();
      rotate();
      back1();
      //rgb read
      b=3;
   }
   
  if (b==6 && j==2 && c==2)
   {
      line_fol();
      h=0;
      b=7;
   }
    if(b==7 && j==7 && c==2)//////j value doubt
    {
//      straight_full();
//      delay(200);
      stop_on_count(95);
      hault();
      c=3;
      j=0;
      rotate();
      throwme_zone3();
      rotate();
      back2();
      //rgb read
      b=3;
   }
   //////////////////////return from zone 3
   if (b==1 && j==5 && c==3)
   {
      straight_full();
      delay(100);
      left_full();
      //right_full();
     // delay(400);
      h=0;
      b=2;
   }
    if(b==2 && j==6 && c==3)
    {
      straight_full();
      delay(100);
      //left_full();
      right_full();
      //delay(400);
      b=9;
   }
   if(b==9 && j==8 && c==3)
   {
     straight_full();
      delay(200);
      hault();
      c=1;
      j=0;
      rotate();
      throwme_zone1();
      rotate();
      back1();
      //rgb read
      b=6;
   }
    if (b==3 && j==5 && c==3)
   {
      line_fol();
      h=0;
      b=4;
   }
    if(b==4 && j==7 && c==3)
    {
//      straight_full();
//      delay(200);
      stop_on_count(85);
      hault();
      c=2;
      j=0;
      rotate();
      throwme_zone2();
      rotate();
      back1();
      //rgb read
      b=6;
   }
  if (b==6 && j==5 && c==3)
   {
      line_fol();
      h=0;
      b=7;
   }
    if(b==7 && j==10 && c==3)
    {
      straight_full();
      delay(200);
      hault();
      c=3;
      j=0;
      rotate();
      throwme_zone3();
      rotate();
      back2();
      //rgb read
      b=3;
   }
    line_fol();
    t.update();
}
