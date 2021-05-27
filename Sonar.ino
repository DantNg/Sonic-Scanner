#include<Servo.h>
#include<string.h>
#define TRIG_PIN 3    //  Trig ---> D3
#define ECHO_PIN 2    //  Echo ---> D2
#define TIME_OUT 10000 // Set Time_out pulseIn 5000 microsecond
//Servo init
Servo alphaServo;
float alpha = 0;

Servo betaServo;
float beta = 0;

  float x = 0;    
  float y = 0;    
  float z = 0;    
  float dist = 0; //cm

// Calculate distance
long getDistance()
{
  long duration, distanceCm;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);
 
  distanceCm = duration / 29.1 / 2;
  
  if(distanceCm > 70)  return 70;   // If the distance exceeds the allowed limit, set equal to 70 
  else if(distanceCm <= 0) return 0; //If distance <= 0 return 0
  else return distanceCm; 
}
/*
//For Scan 2D 
void calPos(float distance , float alpha_angle )
{
  x = distance*cos(alpha_angle*PI/180);
  y = distance*sin(alpha_angle*PI/180);
   Serial.println("Position : " + String(x) + ", " + String(y) );
}
*/
//For Scan 3D
void calPos(long distance , float alpha_angle , float beta_angle)
{
  x = distance*sin(beta_angle*PI/180)*cos(alpha_angle*PI/180);
  y = distance*sin(beta_angle*PI/180)*sin(alpha_angle*PI/180);
  z = distance*cos(beta_angle*PI/180);
  Serial.println(  String(-x,5) + " " + String(y,5)+ " " + String(z,5));
}

void scanSonar()
{
  
   beta = 150; //Set beta servo position = 150 
   betaServo.write(150);

  while ( beta > 5)
  {
    for( alpha = 1 ; alpha<=180;alpha++)
  {
      alphaServo.write(alpha);
      delay(10);
     // calDist();      
      calPos( getDistance() ,alpha, beta );
  }
  beta-=2;
  betaServo.write(beta);
  delay(10);

  for( alpha = 180 ; alpha>0;alpha--)
  {
      alphaServo.write(alpha);
      delay(10);  
     // calDist();      
      calPos( getDistance() ,alpha, beta );    
  }
  beta-=2;
  betaServo.write(beta);
  delay(10);
  }
}
void setup() {
  alphaServo.attach(8);
  betaServo.attach(9);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
 
//  3D MAPPING
// dist = 100;
 scanSonar();
//betaServo.write(0);
//alphaServo.write(0);
//Serial.println(getDistance());

}
