
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
USBHub  Hub1(&Usb); // The controller has a built in hub, so this instance is needed
XBOXOLD Xbox(&Usb);


// Definitions 

int m1_dir1 = 22;
int m1_dir2 = 23;   
int m1_pwm  = 2;

int m2_dir1 = 24;
int m2_dir2 = 25;
int m2_pwm  = 3;
                            // motor driver connections
int m3_dir1 = 26;
int m3_dir2 = 27;
int m3_pwm  = 4;

int m4_dir1 = 28;
int m4_dir2 = 29;
int m4_pwm  = 5;

//---------------------

int encoder1 = 18;
int encoder2 = 19;
int encoder3 = 20;           // encoder connections
int encoder4 = 21;

//---------------------

String val;

void setup() {
  Serial.begin(115200);
  
  for(int i=2;i<=5;i++)
    pinMode(i,OUTPUT)
  for(int i=22;i<=29;i++)
    pinMode(i,OUTPUT)
  for(int i=18;i<=21;i++)
    {
      pinMode(i,INPUT_PULLUP)
      val = isr_m + (i-17);
      attachInterrupt(i, val ,RISING)
    }
    
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // halt
  }
  Serial.print(F("\r\nXBOX Library Started"));
}

void loop() {
  Usb.Task();
  if (Xbox.XboxConnected) {

    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
        Serial.print(F("LeftHatX: "));
        Serial.print(Xbox.getAnalogHat(LeftHatX));
        Serial.print("\t");

        Lefthat_x = Xbox.getAnalogHat(LeftHatX);
        Lefthat_x = map(Lefthat_x,-65535,65535,-255,255);
        
      }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        Serial.print(F("LeftHatY: "));
        Serial.print(Xbox.getAnalogHat(LeftHatY));
        Serial.print("\t");

        Lefthat_y = Xbox.getAnalogHat(LeftHatY);
        Lefthat_y = map(Lefthat_y,-65535,65535,-255,255);
      }
      if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
        Serial.print(F("RightHatX: "));
        Serial.print(Xbox.getAnalogHat(RightHatX));
        Serial.print("\t");

        Righthat_x = Xbox.getAnalogHat(RightHatX);
        Righthat_x = map(Righthat_x,-65535,65535,-255,255);
      }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
        Serial.print(F("RightHatY: "));
        Serial.print(Xbox.getAnalogHat(RightHatY));
        
         Righthat_x = Xbox.getAnalogHat(RightHatX);
         Righthat_y = map(Righthat_y,-65535,65535,-255,255);
      }
      Set_velocity(Lefthat_x,Lefthat_y,Righthat_x);
      
      Serial.println();
    }

    
  }
  delay(1);
}

void Set_velocity(int vx, int vy, int rx)
{
  
  int v1,v2,v3,v4,vtheta,theta;

  rx = vtheta;
  v = sqrt(vx^2 + vy^2);
  theta = atan2(vy,vx);
  
  v1 = v*sin(theta + pi/4) + vtheta;
  v2 = v*cos(theta + pi/4) - vtheta;
  v3 = v*cos(theta + pi/4) + vtheta;
  v4 = v*sin(theta + pi/4) - vtheta;

  if (v1>=0)
  {
    digitalWrite(m1_dir1,HIGH);
    digitalWrite(m1_dir2,LOW);
    }
  else
  {
    digitalWrite(m1_dir1,LOW);
    digitalWrite(m1_dir2,HIGH);    
    }

  analogWrite(m1_pwm, v1);
  analogWrite(m2_pwm, v2);
  analogWrite(m3_pwm, v3);
  analogWrite(m4_pwm, v4);

  
}
