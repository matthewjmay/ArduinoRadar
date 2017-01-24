#include <Servo.h>

int echoPin = 2; //Echo Pin
int trigPin = 3;//Trigger Pin
int rangePin = 13; //Onboard LED
int servoPin = 9; //Ardiino Pin
int maximumRange = 200;
int minimumRange = 0;
int motorposition = 0;
int motorincrement = 1;
long duration, distance; //Duration used to calculate distance

Servo motor;

void setup() {
 motor.attach(servoPin);
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 //pinMode(rangePin, OUTPUT); //out of range indicator
 motor.write(0);
 delay(1000);
}

void loop() {
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 if (motorposition > 179)
  motorincrement = -5;
 else if (motorposition <1)
  motorincrement = 5;
 motorposition += motorincrement;
 motor.write(motorposition);
 
 if (distance >= maximumRange || distance <= minimumRange)
  Serial.println(-1);
 else {
  Serial.println(distance);
  //digitalWrite(LEDPin, HIGH);
 }
 Serial.println(motorposition);
 delay(100);
}
