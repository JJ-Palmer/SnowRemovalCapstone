#define POTM_PIN A0  // potmeter analog input 
#define LIGHTS_PIN 6 // output to FET module
byte pwm;

void setup() {
  Serial.begin(9600);
}

void loop() {
  pwm = 122;
  analogWrite(LIGHTS_PIN, pwm);
  Serial.println(pwm);
  delay(100);
}
