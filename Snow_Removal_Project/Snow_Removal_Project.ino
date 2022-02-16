/*2021-22 Snow Removal Capstone Project controller software.
 * Team Members: Taylor Davis, Phillip Easterbrooks, Daniel Garber, Jared Palmer
 */
#include <OneWire.h>
int tempPin=10; //define D10 as temp input pin
OneWire ds(tempPin);
#define US_TRIG 12 //define D12 as ultrasonic trigger pin 
#define US_ECHO 13 // define D13 as ultrosonic echo pin
#define LIGHT_SENSOR 7
#define RELAY_TRIGGER 6 //
void setup(){
  pinMode(RELAY_TRIGGER, OUTPUT);
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT); 
  
  }
void loop() {
  /*Main Section of program. Triggers voltage out to relay if conditions met from sensors.
  * 
  */
  double temp = Temperature();
  int  dutyCycle =  (-10 * temp) + 255; //FIXME need an equation, variable needs to be 256 (max power) and min working temp and drop to 0 (no power) as temp increases;
  
  while (Snow_Depth() == true && Ambient_Light()==true && temp >= 0){
    analogWrite(RELAY_TRIGGER, dutyCycle);
    }
  }

   
  int Snow_Depth(){
    /* Snow Accumulation sensor, returns integer value of snow depth 
     *  
     */
    double depth = 10.6;
    return true; //FIXME returns true for testing purpose, needs body for this function
  }

  
  bool Ambient_Light(){
    /* Ambient light sensor, returns boolean (true/false) value whether light enough for snow removal or not
    *  
    */
    return true; //FIXME returns true for testing purpose, needs body for this function
  }

  
  double Temperature(){
    /*Temperature Sensor, returns current ambient temperature.
    * 
    */
    double temperature = 24;  //FIXME: returns temp of 10.6 deg for testing purposes
    return temperature;
  }

double temp_to_volt(){
      /*Pulsed output for relay pin. Accepts integer integer input in microseconds
    * as delay between pulses
    */ 
}
