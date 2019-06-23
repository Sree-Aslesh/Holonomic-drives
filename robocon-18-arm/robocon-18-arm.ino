/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/
#include <Servo.h>

// Tsop pin
int tsop = 7;

// Bluetooth var
int bt = 0;

// Tsop Vars
int prev=1;
int current = 0;
int flag=0;
int flag1=1;
int flag2 = 0;
int send1 = 0;

// Time vars 
long long int millis_var = 0;

// Servo var
Servo myservo;// create servo object to control a servo
int servo_pin = 9; //Servo pin

// Flag
int to_do = 1; // 0: for throw

// Tsop delay
int tsop_delay = 0;



void setup() {
  
  Serial.begin(9600);
  myservo.attach(servo_pin);
  myservo.write(80);
  delay(50);
  pinMode(tsop,INPUT);
  
  }

void loop() {
  // For bluetooth comm.
 // bt=1;
if(Serial.available())
  
  {
    //Serial.println("jjjjjjjjjjjjj");
    bt =Serial.read();
  }
  //Serial.println(bt);
  
  if(bt == 1 || flag1 == 0)
    {
      tsop_delay = 0;
      myservo.write(0);
      //Serial.write(2);
      //Serial.print("handle");
      flag1 = 0;
      flag = 0;
      
     // to_do =0;
      
    }
    
  
  
 /* // For gripping of shuttle
 if(bt == 1)
 {myservo.write(90); // open position
  delay(2500);
 myservo.write(0);// close position
delay(3000);
 bt = 0;
 flag = 0; // Gripping restarted
 }*/

if(bt == 2)
{
 // For tsop detection and shuttle release
  flag1 = 1;
 if(tsop_delay == 0)
 {
  delay(3000);
  tsop_delay = 1;
 }


 current = digitalRead(tsop);
 
 if(current != prev)
  {
    flag++;
   
  prev = current;
  }
  if(flag>=1)
    {
      myservo.write(90);
      Serial.write(2);//Shuttle released
      flag = 0;
      bt=0;
      
     //Serial.print("thrown");
      
      
    /*delay(4000);
    myservo.write(90); 
      flag = 1;
      Serial.write(0);*/  
    }
    
    }

}

