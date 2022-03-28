/*2021-22 Snow Removal Capstone Project controller software.
 * Team Members: Taylor Davis, Phillip Easterbrooks, Daniel Garber, Jared Palmer
 */
#include <OneWire.h>

int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2
//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2
#define US_TRIG 12 //define D12 as ultrasonic trigger pin 
#define US_ECHO 13 // define D13 as ultrosonic echo pin
#define LIGHT_SENSOR 4
#define RELAY_TRIGGER 6 //
void setup(){
  pinMode(RELAY_TRIGGER, OUTPUT);
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
  float temp;

  }
void loop() {
  /*Main Section of program. Triggers voltage out to relay if conditions met from sensors.
  * 
  */
  temp = Temperature();
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
   bool flag = false;
   int brightness = analogRead(LIGHT_SENSOR);
   if brightness > 80 { //FIXME estimated this val based on sensor val from cloudy evening in my office.
     flag = true;
   }
    return flag; 
  }

  
  float Temperature(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  }

double temp_to_volt(){
      /*Pulsed output for relay pin. Accepts integer integer input in microseconds
    * as delay between pulses
    */ 
}
