/*2021-22 Snow Removal Capstone Project controller software.
 * Team Members: Taylor Davis, Phillip Easterbrooks, Daniel Garber, Jared Palmer
 */
#include <OneWire.h>
int tempPin=10; //define D10 as temp input pin
OneWire ds(tempPin);
#define US_TRIG 12
#define US_ECHO 13
#define LIGHT_SENSOR 7
#define RELAY_TRIGGER 5
void setup(){
  pinMode(RELAY_TRIGGER, OUTPUT);
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT); 
  
  }
void loop() {
  /*Main Section of program. Triggers voltage out to relay if conditions met from sensors.
  * 
  */
  int temp = Temperature();
  int  pulseDelay =  (temp + 100)/60; //FIXME: need to develop an equation to correspond pulse delay to temperature.

  while (Snow_Depth()==true && Ambient_Light()==true && temp >= 0){
    pulseOut(pulseDelay);
    }
  }

   
  int Snow_Depth(){
    /* Snow Accumulation sensor, returns integer value of snow depth 
     *  
     */

  }

  
  bool Ambient_Light(){
    /* Ambient light sensor, returns boolean (true/false) value whether light enough for snow removal or not
    *  
    */
  }

  
  int Temperature(){
    /*Temperature Sensor, returns current ambient temperature.
    * 
    */
   
  }
  
  void pulseOut(int us){
    /*Pulsed output for relay pin. Accepts integer integer input in microseconds
    * as delay between pulses
    */
    digitalWrite(RELAY_TRIGGER, HIGH);
    us = max(us-20,1);
    delayMicroseconds(us);
    digitalWrite(RELAY_TRIGGER,LOW);
  }
