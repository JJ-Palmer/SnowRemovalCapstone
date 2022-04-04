/*2021-22 Snow Removal Capstone Project controller software.
 * Team Members: Taylor Davis, Phillip Easterbrooks, Daniel Garber, Jared Palmer
 */

#include <OneWire.h>

int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2
OneWire ds(DS18S20_Pin);  // on digital pin 2
#define US_TRIG 12 //define D12 as ultrasonic trigger pin 
#define US_ECHO 13 // define D13 as ultrosonic echo pin
#define LIGHT_SENSOR 4
#define RELAY_TRIGGER 6 //
int value = 0;
const unsigned int TRIG=12;
const unsigned int ECHO=13;
const unsigned int vcc =11;




void setup(){
  pinMode(RELAY_TRIGGER, OUTPUT);
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);


  }
/********************************
*********************************
********************************/   
void loop() {
  /*Main Section of program. Triggers voltage out to relay if conditions met from sensors.
  * 
  */
  double depth = Snow_Depth();
  double temp = Temperature();
  double V = temp_to_volt(depth,temp);
  if (depth > 4.0 && Ambient_Light()==true && temp>-18 ){
    int  dutyCycle =  255*(V/12); // 
    if (dutyCycle > 12) {
      dutyCycle = 12;
      }
    analogWrite(RELAY_TRIGGER, dutyCycle);
    }
  else {
    digitalWrite(RELAY_TRIGGER, LOW);  
    }
   delay(60000); //reasseses all values every minute
  }
/********************************
*********************************
********************************/    
double Snow_Depth(){
    /* Snow Accumulation sensor, returns integer value of snow depth 
     *  
     */
  digitalWrite(vcc, HIGH);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  //convert time inbetween pulses into centimeters

  const unsigned long  duration= pulseIn(ECHO, HIGH);
  double distance= duration/58;
  double depth = 35 - distance;

  }
/********************************
*********************************
********************************/  
  bool Ambient_Light(){
    /* Ambient light sensor, returns boolean (true/false) value whether light enough for snow removal or not
    *  
    */
   bool flag = false;
   int brightness = analogRead(LIGHT_SENSOR);
   if (brightness < 80) { //FIXME estimated this val based on sensor val from cloudy evening in my office.
     flag = true;
     }
    return flag; 
  }
/********************************
*********************************
********************************/   
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
/********************************
*********************************
********************************/  
double temp_to_volt(double depth,double temp){
      /*Pulsed output for relay pin. Accepts integer integer input in microseconds
    * as delay between pulses
    */ 
  double Th = 27;
  double A = 0.418;
  double ksn = 0.3;
  //double tsn = 0.04; 
  double Ri = 8.8859;
  double Rair = 0.694;
  double Rpanel = 0.575;
  double Rsn = depth/(ksn*A);
  double V = 0;
  double Q = (Th - temp)*(1/(Rpanel+Rsn+Rair)+1/(Ri+Rair)); //
  if (Q >= 0) {
    double V = sqrt(Q*0.9); //Voltage required as a fn of Q
  }
  return V;
}
