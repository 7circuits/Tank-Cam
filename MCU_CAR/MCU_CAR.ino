
#include <Servo.h>
//MotorPins
int pinLB = 12;     // define pin 12 Digital SPI/MISO
int pinRB = 13;    // define pin 13 Digital SPI/SCK
int pinLF = 3;     // define pin 3 Digital PWM
int pinRF = 11;    // define pin 11 Digital PWM
int val;

int Fspeedd = 0;      // forward speed
int Rspeedd = 0;      // right speed
int Lspeedd = 0;      // left speed
int directionn = 0;   // forward=8 backward=2 left=4 right=6 
Servo HorServo;        // Horitzontal Servo
Servo VerServo;       // Vertical Servo
int delay_time = 250; // settling time after steering servo motor moving B

int HorPos;
int HorMid = 100;
int VerPos;
int VerMid = 80;

void setup()
{
    Serial.begin(115200);     // define pin for motor output 
    pinMode(pinLB,OUTPUT); // pin 12
    pinMode(pinLF,OUTPUT); // pin 3 (PWM)
    pinMode(pinRB,OUTPUT); // pin 13
    pinMode(pinRF,OUTPUT); // pin 11 (PWM) 
  
    HorServo.attach(9);    // Define servo motor output pin to D9 (Digital PWM)
    HorServo.write(HorMid);  // home set the servo motor, ready for next measurement
    VerServo.attach(6);    // Define servo motor output pin to D6 (Digital PWM)
    VerServo.write(VerMid);  // home set the servo motor, ready for next measurement
    HorPos = HorMid;
    VerPos = VerMid;
}
 
void advance()     // move forward
{ 
    digitalWrite(pinLB,LOW);    // right wheel moves forward
    digitalWrite(pinRB, LOW);  // left wheel moves forward
    analogWrite(pinLF,210);   
    analogWrite(pinRF,255);
}
    
void stopp()         // stop
{
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinRB,HIGH);
     analogWrite(pinLF,0);
     analogWrite(pinRF,0); 
}
    
void right()        // turn right
{
   digitalWrite(pinLB,HIGH);  // left wheel moves forward
   digitalWrite(pinRB,LOW); // right wheel moves backward
   analogWrite(pinLF, 255);
   analogWrite(pinRF,255);   
}
    
void left()         // turn left
{
  digitalWrite(pinLB,LOW);  // left wheel moves forward
  digitalWrite(pinRB,HIGH); // right wheel moves backward
  analogWrite(pinLF, 255);
  analogWrite(pinRF,255);  
}
    
void back()          // move backward
{
  digitalWrite(pinLB,HIGH);  // motor moves to left rear
  digitalWrite(pinRB,HIGH);  // motor moves to right rear
  analogWrite(pinLF,210);  
  analogWrite(pinRF,255);     
}

void camri()
{
  if (HorPos >= 15)
  {
    HorPos = HorPos -5;
    HorServo.write(HorPos);
  }
  else
  {
    HorPos = 10;
    HorServo.write(HorPos);
  }
}

void camle()
{
  if (HorPos <=165)
  {
  HorPos = HorPos +5;
  HorServo.write(HorPos);
  }
  else
  {
    HorPos = 170;
    HorServo.write(HorPos);
  }
}

void camup()
{
  if (VerPos <=165)
  {
  VerPos = VerPos +5;
  VerServo.write(VerPos);
  }
  else
  {
    VerPos = 170;
    VerServo.write(VerPos);
  }
}

void camdn()
{
  if (VerPos >= 15)
  {
    VerPos = VerPos -5;
    VerServo.write(VerPos);
  }
  else
  {
    VerPos = 10;
    VerServo.write(VerPos);
  }
}

void cammi()
{
  VerServo.write(VerMid);
  VerPos = VerMid;
  delay(200);
  HorServo.write(HorMid);
  HorPos = HorMid;
  delay(200);
}
    
void loop()
{ 
  val=Serial.read(); 
  if(val=='G')advance();
  if(val=='B')back();
  if(val=='L')left();
  if(val=='R')right();
  if(val=='S')stopp();
  if(val=='O')camle();
  if(val=='P')camri();
  if(val=='M')cammi();
  if(val=='F')camup();
  if(val=='T')camdn();
  //delay(5);
}
