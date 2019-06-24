float Kp = 5;
//const int Ki = 0;
float Kd = 0;  
float setPoint = 35; 
float baseSpeed = 70;  
float maxSpeed = 170;  
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
  analogWrite(L1PWM,200);
  analogWrite(L2PWM,200);
  analogWrite(R1PWM,200);
  analogWrite(R2PWM,200);
   ls_for=((float)analogRead(A2)/921)*70;
   Serial.println(ls_for);
  }
  while(ls_for>= 60)
 {
  left();
  analogWrite(L1PWM,200);
  analogWrite(L2PWM,200);
  analogWrite(R1PWM,200);
  analogWrite(R2PWM,200);
  ls_for=((float)analogRead(A2)/921)*70;
  Serial.println(ls_for);
}
}

void right_full()
{
 while(ls_for< 75)
  {
  right();
  analogWrite(L1PWM,200);
  analogWrite(L2PWM,200);
  analogWrite(R1PWM,200);
  analogWrite(R2PWM,200);
  ls_for=((float)analogRead(A2)/921)*70;
  }
 while(ls_for>= 60)
 {
  right();
  analogWrite(L1PWM,200);
  analogWrite(L2PWM,200);
  analogWrite(R1PWM,200);
  analogWrite(R2PWM,200);
  ls_for=((float)analogRead(A2)/921)*70;
}
}
void straight_full()
{
  straight();
  analogWrite(L1PWM,100);
  analogWrite(L2PWM,100);
  analogWrite(R1PWM,100);
  analogWrite(R2PWM,100);
}
void throwme()
{
  delay(2000);
  h=0;
}
float read_ls()
{
  for(k=22;k<=29;k++)
  {
    a[k-22]=digitalRead(k); 
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
    Serial.print("line following ");
    Serial.print(ls_for);
    // If no line is detected, stay at the position
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
    //Serial.println(motorSpeed);
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
    Serial.println("left motor  ");
    Serial.println(leftMotorSpeed);
    Serial.println("right motor  ");
    Serial.println(rightMotorSpeed);
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
    Serial.print("line  ");
    Serial.print(ls);
    // If no line is detected, stay at the position
    if(ls >= 75)
    {
       wait();
    }

    // Else if line detected, calculate the motor speed and apply
  else {
    float error1 = ls - setPoint;   
    //integral = integral + error
    motorSpeed1 =(Kp * error1 + Kd * (error1 - lastError1));//+ Ki*integral;
    lastError1 = error1;    
    //Serial.println(motorSpeed);
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
    Serial.println("left motor1  ");
    Serial.println(leftMotorSpeed1);
    Serial.println("right motor1  ");
    Serial.println(rightMotorSpeed1);
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
  attachInterrupt(digitalPinToInterrupt(18),count1,RISING);
  attachInterrupt(digitalPinToInterrupt(20),count2,RISING);
  attachInterrupt(digitalPinToInterrupt(21),count3,RISING);
  while(c0 < abb)
  {
    c0 = (c1+c2+c3)/3;
    straight();
    Serial.println("count of c");
    Serial.print(c);
    Serial.println("count of a");
    Serial.print(abb);
    analogWrite(L1PWM,80);
    analogWrite(L2PWM,80);
    analogWrite(R1PWM,80);
    analogWrite(R2PWM,80);
  }
  wait();
  c1 =0;
  c2 =0;
  c3 =0;
  detachInterrupt(digitalPinToInterrupt(18));
  detachInterrupt(digitalPinToInterrupt(20));
  detachInterrupt(digitalPinToInterrupt(21));

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
        stop_on_count(60);
        hault();
        delay(2000);//recieving shuttlecock
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
        
        hault();
        delay(2000);
        h=0;
}
}

 


void setup() {
  pinMode(A2,INPUT);
  pinMode(junctionPulse,INPUT); 
  for(i=22;i<=29;i++)
  {
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
  for(i=2;i<=14;i++)
   {
    pinMode(i,OUTPUT);
   }

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
      b=2;
      Serial.println('h');
      Serial.println(h);
      Serial.println('c');
      Serial.println(c);
      Serial.println('j');
      Serial.println(j);
      //delay(2000);
  }
  
  if (b==2 && j==3 && c==0)
    {
//      straight_full();
//      delay(200);
      hault();
      stop_on_count(60);
      c=1;
      j=0;
      throwme();
      back1();
      //rgb read
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
      stop_on_count(60);
      hault();
      c=1;
      j=0;
      throwme();
      back1();
      //rgb read
      b=3;
   }
   if (b==3 && j==2 && c==1)
   {
//      straight_full();
//      delay(200);
      right_full();
      h=0;
      b=4;
   }
    if(b==4 && j==3 && c==1)
    {
      straight_full();
      delay(200);
      left_full();
      b=5;
   }
   if(b==5 && j==5 && c==1)
   {
     straight_full();
      delay(200);
      hault();
      c=2;
      j=0;
      throwme();
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
      throwme();
      back2();
      //rgb read
      b=3;
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
      throwme();
      back1();
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
      throwme();
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
      straight_full();
      delay(200);
      hault();
      c=3;
      j=0;
      throwme();
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
      throwme();
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
      straight_full();
      delay(200);
      hault();
      c=2;
      j=0;
      throwme();
      back1();
      //rgb read
      b=3;
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
      throwme();
      back2();
      //rgb read
      b=3;
   }
    line_fol();

}
