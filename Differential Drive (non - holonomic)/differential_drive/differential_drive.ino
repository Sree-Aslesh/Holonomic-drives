int junctionPulse = A1;
int j=0;
int b=1;
int h=0;
int c=0;
const int Kp = 1.5;
const int Ki = 0;
const int Kd = 0.6;  
const int setPoint = 35; 
const int baseSpeed = 190;  
const int maxSpeed = 255;  
int integral=0;
int lastError = 0;
int motorSpeed;
float a;
int i;
int L1CW=2;
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
  digitalWrite(L1CW,HIGH);
  digitalWrite(L1CCW,HIGH);
  digitalWrite(L2CW,HIGH);
  digitalWrite(L2CCW,HIGH);
  digitalWrite(R1CW,HIGH);
  digitalWrite(R1CCW,HIGH);
  digitalWrite(R2CW,HIGH);
  digitalWrite(R2CCW,HIGH);
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
  analogWrite(L1PWM,0);
  analogWrite(L2PWM,0);
  analogWrite(R1PWM,0);
  analogWrite(R2PWM,0);
  h=1;
}
void line_fol()
{
  if(h==0)
  {
    a=((float)analogRead(A0)/710)*70;
     Serial.println(a);
    
    // If no line is detected, stay at the position
    if(a >= 75)
    {
       wait();
    }

  // Else if line detected, calculate the motor speed and apply
  else {
    int error = a - setPoint;   
    //integral = integral + error;
    motorSpeed = 25.8*(Kp * error + Kd * (error - lastError));//+ Ki*integral;
    lastError = error;    
    //Serial.println(motorSpeed);
    int rightMotorSpeed = baseSpeed - motorSpeed;
    int leftMotorSpeed = baseSpeed + motorSpeed;
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
    a=((float)analogRead(A0)/710)*70;
     Serial.println(a);
    
    // If no line is detected, stay at the position
    if(a >= 75)
    {
       wait();
    }

  // Else if line detected, calculate the motor speed and apply
  else {
    int error = a - setPoint;   
    //integral = integral + error;
    motorSpeed = 25.8*(Kp * error + Kd * (error - lastError));//+ Ki*integral;
    lastError = error;    
    //Serial.println(motorSpeed);
    int rightMotorSpeed = baseSpeed - motorSpeed;//doubt here
    int leftMotorSpeed = baseSpeed + motorSpeed;//doubt here
    reverse();

    // If the speed of motor exceed max speed, set the speed to max speed
    if(rightMotorSpeed > maxSpeed) rightMotorSpeed = maxSpeed;
    if(leftMotorSpeed > maxSpeed) leftMotorSpeed = maxSpeed;

    reverse();
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
   
   analogWrite(L1PWM,abs(leftMotorSpeed));
   analogWrite(L2PWM,abs(leftMotorSpeed));
   analogWrite(R1PWM,abs(rightMotorSpeed));
   analogWrite(R2PWM,abs(rightMotorSpeed));
  }
  }
}


void left_full()
{
  while(a< 76)
  {
  left();
  analogWrite(L1PWM,255);
  analogWrite(L2PWM,255);
  analogWrite(R1PWM,255);
  analogWrite(R2PWM,255);
   a=((float)analogRead(A0)/710)*70;
   Serial.println(a);
  }
  while(a>= 60)
 {
    left();
  analogWrite(L1PWM,255);
  analogWrite(L2PWM,255);
  analogWrite(R1PWM,255);
  analogWrite(R2PWM,255);
  a=((float)analogRead(A0)/710)*70;
  Serial.println(a);
}}
void right_full()
{
 while(a< 76)
  {
  right();
  analogWrite(L1PWM,255);
  analogWrite(L2PWM,255);
  analogWrite(R1PWM,255);
  analogWrite(R2PWM,255);
  a=((float)analogRead(A0)/710)*70;
  }
 while(a>= 70)
 {
  right();
  analogWrite(L1PWM,255);
  analogWrite(L2PWM,255);
  analogWrite(R1PWM,255);
  analogWrite(R2PWM,255);
  a=((float)analogRead(A0)/710)*70;
}
}
void straight_full()
{
  straight();
  analogWrite(L1PWM,200);
  analogWrite(L2PWM,200);
  analogWrite(R1PWM,200);
  analogWrite(R2PWM,200);
}
void throwme()
{
  delay(2000);
  h=0;
}
void back1()
{
      
      while(j!=2)
      {
        if(digitalRead(junctionPulse)) 
        {
            while(digitalRead(junctionPulse)) 
            {
              Serial.println("detecting");
            }
         j++;
        }
        line_fol_back();
      }
      if(j==2)
      {
        
        hault();
        delay(2000);//recieving shuttlecock
        h=0;
}
}
void back2()
{
      while(j!=4)
      {
        if(digitalRead(junctionPulse)) 
        {
            while(digitalRead(junctionPulse)) 
            {
              Serial.println("detecting");
            }
         j++;
        }
        line_fol_back();
      }
      if(j==4)
      {
        
        hault();
        delay(2000);
        h=0;
}}
void setup() 
{
  // put your setup code here, to run once:
  
  pinMode(A0,INPUT);
  Serial.begin(9600);
  for(i=2;i<=13;i++)
   {
    pinMode(i,OUTPUT);
   }
  pinMode(junctionPulse,INPUT); 
  
}

void loop() {
  a=((float)analogRead(A0)/921)*70;
  Serial.println(a);
  
  if(digitalRead(junctionPulse)) {
    while(digitalRead(junctionPulse)) {
      Serial.println("detecting");
      }
    j++;
  }
  
//  Serial.println("junction ");
//  Serial.println(j);
//  Serial.println("b");
//  Serial.println(b);
  if (b==1 && j==1 && c==0)
  {
   
      straight_full();
      delay(800);
      left_full();
      delay(400);
      b=2;
  }
  
  if (b==2 && j==3 && c==0)
    {
      straight_full();
      delay(800);
      hault();
      c=1;
      j=0;
      throwme();
      back1();
      //rgb read
      b=1;
    }
   if (b==1 && j==2 && c==1)
   {
      line_fol();//start here
      h=0;
      b=2;
   }
    if(b==2 && j==4 && c==1)
    {
      straight_full();
      delay(800);
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
      straight_full();
      delay(800);
      right_full();
      delay(400);
      h=0;
      b=4;
   }
    if(b==4 && j==3 && c==1)
    {
      straight_full();
      delay(800);
      left_full();
      delay(400);
      b=5;
   }
   if(b==5 && j==5 && c==1)
   {
     straight_full();
      delay(800);
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
      straight_full();
      delay(800);
      right_full();
      delay(400);
      h=0;
      b=7;
   }
    if(b==7 && j==3 && c==1)
    {
      straight_full();
      delay(800);
      left_full();
      delay(400);
      b=8;
   }
   if(b==8 && j==7 && c==1)
   {
     straight_full();
      delay(800);
      hault();
      c=3;
      j=0;
      throwme();
      back2();
      //rgb read
      b=1;
   }
   
   if (b==1 && j==2 && c==2)
   {
      straight_full();
      delay(800);
      left_full();
      delay(400);
      h=0;
      b=2;
   }
    if(b==2 && j==3 && c==2)
    {
      straight_full();
      delay(800);
      right_full();
      delay(400);
      b=9;
   }
   if(b==9 && j==5 && c==1)
   {
     straight_full();
      delay(800);
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
      straight_full();
      delay(800);
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
    if(b==7 && j==6 && c==2)
    {
      straight_full();
      delay(800);
      hault();
      c=3;
      j=0;
      throwme();
      back2();
      //rgb read
      b=3;
   }
   ///////////////////////////
   if (b==1 && j==4 && c==3)
   {
      straight_full();
      delay(800);
      right_full();
      delay(400);
      h=0;
      b=2;
   }
    if(b==2 && j==5 && c==3)
    {
      straight_full();
      delay(800);
      left_full();
      delay(400);
      b=9;
   }
   if(b==9 && j==7 && c==3)
   {
     straight_full();
      delay(800);
      hault();
      c=1;
      j=0;
      throwme();
      back1();
      //rgb read
      b=6;
   }
    if (b==3 && j==4 && c==3)
   {
      line_fol();
      h=0;
      b=4;
   }
    if(b==4 && j==6 && c==3)
    {
      straight_full();
      delay(800);
      hault();
      c=2;
      j=0;
      throwme();
      back1();
      //rgb read
      b=3;
   }
  if (b==6 && j==4 && c==3)
   {
      line_fol();
      h=0;
      b=7;
   }
    if(b==7 && j==8 && c==3)
    {
      straight_full();
      delay(800);
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


