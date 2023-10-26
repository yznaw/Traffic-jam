// Wire Slave sender
//send data to Master via i2c

#include <Wire.h>
int inPin1 = 2;  
int inPin2 = 4;
int inPin3 = 7;


void setup() {
   Serial.begin(9600);      // start serial for output
pinMode(inPin1,INPUT);      //we define the pins as input 
pinMode(inPin2,INPUT);
pinMode(inPin3,INPUT);
  
 Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {  
  Serial.println(digitalRead(inPin1));    //print on serial monitor just for testing 
  Serial.print(digitalRead(inPin2));
  Serial.print(digitalRead(inPin3));
 delay(500);
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()

void requestEvent() {  
 int read1=digitalRead(inPin1);   //Reads the value from a specified digital pin
 int read2=digitalRead(inPin2); 
 int read3=digitalRead(inPin3);
 int count=read1+read2+read3;
  Wire.write(count);
 }

