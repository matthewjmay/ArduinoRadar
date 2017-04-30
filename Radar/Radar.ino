#include <Servo.h>

int echoPin = 2; //Echo Pin
int trigPin = 3;//Trigger Pin
int rangePin = 13; //Onboard LED
int servoPin = 9; //Ardiino Pin
int maximumRange = 200;
int minimumRange = 0;
int motorposition = 0;
int motorincrement = 3;
long duration;
int distance; //Duration used to calculate distance

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
 distance = int(duration)/58;
 if (motorposition > 179 || motorposition < 1)
  motorincrement *= -1;
 motorposition += motorincrement;
 motor.write(motorposition);
 String sending = "";
 if (distance >= maximumRange || distance <= minimumRange)
  sending += "-1";
 else
  sending += String(distance);
 sending += ("." + String(motorposition));

 int strlength = sending.length()+1;
 char* tosend = new char[strlength];
 sending.toCharArray(tosend, strlength);
 
 Serial.println(tosend);
 delete tosend;
 delay(150);
}
