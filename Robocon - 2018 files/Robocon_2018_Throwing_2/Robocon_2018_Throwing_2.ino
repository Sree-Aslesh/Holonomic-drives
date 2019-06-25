// read RPM
//Interrupt vars
#include <Servo.h>
volatile int rpmcount = 0;
int flag11 = 1;
unsigned long first = 0;
int attach_inter  = 0;
//Servo Params
Servo myservo;
int angle = 0;
// Target rpm
float rpm =0.0;
float setp = 140;

// Time recorder
unsigned long lastmillis = 0;

// Motor info
int pwm = 6;
int dir1 = 12;
int dir2 = 11;
int flag10=0;



// PID params
float kp = 0.000027;
float kd = 0.028;
float ki = 0;
float base = 35;
//int tsop1=8;

// Error vars
float error = 0 ;
float last = 0;
float derr = 0;
float pid = 0;
float mult = 1;
double err_sum = 0;
double max_err_sum = 400;

// Count vars
int count=0;
int rounds=0;
int iread=0;//change!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
long cc;
int cnt = 0;
long long int lasttime = 0;

// Master flags 
int Stopflag=0;
int Stopflag1=0;

int flag9 = 0;
int flag20 = 0;
int channel_flag = 2; // 

char to_do = "";
char drive_flag = ""; // Drive flag        1: For zone 1, 2: For zone 2, 3: For zone 3, t: For throwing, g: For gripping, s: Stop at 90   
//char zone = "";
int flag8 = 1;

// Tsop
int tsop = 7;
int tsop_var = 1;
int prev_tsop = 1;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Stop var
int stop1 = 0;
int stop_pwm = 100;
int direction1 = 0;
int flagtsop =1;

// Reaching 90 vars
int small_pwm = 45;
int stop_opp = 0;        ///////////// Opposite rpm flag///////////////////////////////////

// IR vars
int flag1 = 0;

int countt=0;
// Channel vars
int channel_recieve = 2;


// Drive recieving bits
int rec_bit1_pin = A0; // Grey 
int rec_bit2_pin = A1; // Purple
int idle_bit_pin = A2; // Blue

int rec_bit1 = 0;    //bit1 bit 2 bit 3        001: for zone1, 010: for zone2, 011: for zone3, 100: for gripping,101: for stop at 90     
int rec_bit2 = 0;
int idle_bit = 0;

// Drive sending bits
int feedback = A3;  // Green
//int send_bit = 0;

//****************** The ground pin for inter arduino data bits is yellow coloured 


// Functions 
//*******************************************
void stop_at_90();
void cal_and_set_rpm1();
void zone_set(int angle);
void rpm_fan();
void Null();
void Null1();
//*******************************************



void setup() {
  pinMode(3,INPUT_PULLUP);
  pinMode(7,INPUT);
Serial.begin(9600); // comment it
  attachInterrupt(0, rpm_fan, RISING); 
 // attachInterrupt(1, stop11, FALLING);
  pinMode(pwm, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(tsop,INPUT);
  pinMode(rec_bit1_pin,INPUT);
  pinMode(rec_bit2_pin,INPUT);
  pinMode(idle_bit_pin,INPUT);
  pinMode(feedback,OUTPUT);
  pinMode(8,OUTPUT);
  myservo.attach(10);
  myservo.write(35);
   to_do = 's';
}

void loop() 
{
   Serial.println(digitalRead(3));  
  rec_bit1 = digitalRead(rec_bit1_pin);
  rec_bit2 = digitalRead(rec_bit2_pin);
  idle_bit = digitalRead(idle_bit_pin);
// Serial.print(rec_bit1);
 //Serial.print(rec_bit2);
 //Serial.println(idle_bit);
 //Serial.print("          ");
  if(Serial.available()>0)
  {
    channel_flag = Serial.read();
    
    if(channel_flag == 2)
    {
    to_do = 'r'; // set to either null or null1
    ////Serial.println("in in in in in in ");
    digitalWrite(feedback,1);
    }
  // 
  }
  if(idle_bit == 0 ) // If the bit stream is not empty
  {
    

    //*************************** Flag management ************************
    if(rec_bit1 == 1 && rec_bit2 == 1) // Stop at 90
    {
    to_do = 's';
    }
   if(rec_bit1 == 0 && rec_bit2 == 0) // Set params for zone 1
    {angle = 60;
     setp = 125;
     //zone_set(angle); 
     to_do = 't';
     Serial.write(2);
    }
  if(rec_bit1 == 0 && rec_bit2 == 1) // Set params for zone 2
  {
    angle = 50;
    setp = 150;
    //zone_set(angle); 
        to_do = 't'; 
        Serial.write(2);
  }
    
    if(rec_bit1 == 1 && rec_bit2 == 0) // Set params for zone 3
    {
    angle = 45;
    setp = 170;
    //zone_set(angle); 
        to_do = 't';
        Serial.write(2);
    }
    
  /*  if(rec_bit1 == 1 && rec_bit2 == 0) // For gripping of shuttle
    {
      Serial.write(1);
      delay(100);
      
    }*/
  }
    else if(idle_bit == 1 )
    {
      to_do = 'n';
      digitalWrite(feedback,0);
      
    }
    
    /*if(drive_flag == 't')
    {
      Serial.write(1);
      delay(700);
      to_do = 't';
    }*/
    
  
 // ******************* Flag Selection ********************************//
 if(to_do == 't')  // For throwing
 {
  //myservo.write(50);
  cal_and_set_rpm1();
 }
 
 else if(to_do == 's')  // For stopping at 90
 {
  stop_at_90();
 }
 
 else if(to_do == 'n') // For waiting
 {
  Null();
 }
 else if(to_do == 'r') // For waiting
 {
  Null1();
 }
  
}


void rpm_fan() { /* this code will be executed every time the interrupt 0 (pin3) gets low.*/
  rpmcount++;
  count++;
// //Serial.println(count);

  }

  void stop11()  // Executed when second tsop detects 
 {
  Serial.println("interrupt is called ");
//  Serial.println(digitalRead(3));
  Serial.println(digitalRead(3));  
 while(digitalRead(7)==1 && countt<40000)
  {
    // Serial.println(digitalRead(3));
 digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    analogWrite(pwm,15);
    countt++;
    Serial.println("ppppppppppppppppp");
   
  }
  
 
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
    analogWrite(pwm,25);
    delay(45);
   // Serial.println("ssssssssssssss");
      
   
   /*if (cnt<=1)
 {
 digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    analogWrite(pwm,255);
delay(300);
 
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    analogWrite(pwm,0);
    cnt++;
 }*/
 }

  

void stop_at_90()
{
       
   attachInterrupt(digitalPinToInterrupt(3), stop11, FALLING); // 2nd tsop is on interrupt   
   //attach_inter = 1;
   ////Serial.println("handle");
   
  
  ////Serial.println("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
  Stopflag=digitalRead(tsop);
  //Stopflag1=digitalRead(tsop1);
 // stopflag1=digitalRead(tsop1);
  ////Serial.println(Stopflag);
  // Tsop changed to IR please change it back for abhinav's sake !!!

  if(Stopflag == 1 && flag9==0)
  {
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
    analogWrite(pwm,34);
    //Serial.println("rrrrrr");
   // flag20 = 0;
    
    
    //Serial.write(2);
  }
  
 else if(Stopflag==0 || flag9==1)
  {
    

    // applying opposite pwm to counter inertia
   /*if(stop_opp == 0)
    {
      digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    analogWrite(pwm,50);
    delay(55);
    stop_opp = 1;
    }*/
    ///////////////////
    
  //  //Serial.println("ggggggggggggggg");
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
    analogWrite(pwm,8);
    flag9=1;
 //  //Serial.println("send"); 

// //Serial.println("send");
delay(4000);
    Serial.write(1);
    
    delay(2000);
    digitalWrite(feedback,HIGH);
    //Serial.println("ho gayaaaa");
   // delay(1000);
  to_do='n';
  delay(500);//r_pi time
 
 }
 
  
  
  
 /* if(Stopflag1==0)
  {

    // applying opposite pwm to counter inertia
  /*  if(stop_opp == 0)
    {
      digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    analogWrite(pwm,50);
    delay(55);
    stop_opp = 1;
    }*/
    ///////////////////
    
  ////  //Serial.println("ggggggggggggggg");
   //digitalWrite(dir1,HIGH);
   //digitalWrite(dir2,LOW);
   //analogWrite(pwm,5);
    
 //  //Serial.println("send"); 
     //}
      detachInterrupt(digitalPinToInterrupt(3));
}





void cal_and_set_rpm1()
{
  //**************** Open loop pwm

 // //Serial.println("throw");
  
  //myservo.write(0);//set angle
  //float setp = 140;//set rpm
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  //analogWrite(pwm,255);
  if (millis() - lastmillis == 100) { /*Uptade every one second, this will be equal to reading frecuency (Hz).*/

    detachInterrupt(0);    //Disable interrupt when calculating


    rpm = (rpmcount * 600.0) / 135.0 ; /* Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use rpmcount * 30.*/

    //Serial.print("RPM =\t"); //print the word "RPM" and tab
   ////Serial.println(rpm); // print the rpm value.
    //Serial.print("\t Hz=\t"); //print the word "Hz".
    ////Serial.println(pid/*rpmcount*/); /*print revolutions per second or Hz. And print new line or enter.*/

    rpmcount = 0; // Restart the RPM counter
    lastmillis = millis(); // Uptade lasmillis
    attachInterrupt(0, rpm_fan, RISING); //enable interrupt
  }
  error = (setp - rpm);
  derr = last - error;
 
  pid = pid + (kp * error) + (kd * derr) + (ki * err_sum) ;
   if (pid<80)
  {
    pid=100;
  }
  
  last = error;
  err_sum = err_sum + error;
  if (err_sum > max_err_sum)
  {
    err_sum = max_err_sum;
  }
  if (err_sum < -max_err_sum)
  {
    err_sum = -max_err_sum;
  }
  if (pid < 255 && pid > 0) {
    analogWrite(pwm, (int)pid); //set motor speed
  }
  else {
    if (pid > 255) {
      //pid = 255;
      analogWrite(pwm, 255);
    }
    if (pid < 0) {
      //pid = 0;
      analogWrite(pwm, 0);
    }


  }
  flag9 = 0;
  stop_opp = 0;//////////// opposite rpm flag
  flag20 = 0;
/*  if(attach_inter == 1)
  {
    attach_inter = 0;
  }*/
  cnt = 0;
  countt=0;
}



void zone_set(int angle)
{
  myservo.write(angle);
 delay(150);
  
}

void Null()
{
 // //Serial.println("null111111111");
 // //Serial.println("null");
   digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    analogWrite(pwm,12);
  
  
}
void Null1()
{
  digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    analogWrite(pwm,12);
}


