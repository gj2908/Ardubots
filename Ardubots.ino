#include <SoftwareSerial.h>
#define MQ2pin (0)
int x=5;
int y=10;
const int buzzer = 13; //buzzer to arduino pin 13
const int lm35_pin = 25;	/* LM35 O/P pin */

float sensorValue;  //variable to store sensor value
int measurePin = A4;   // Connect dust sensor to Arduino A4 pin
int ledPower = 2;      // Connect dust sensor LED driver pin to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
SoftwareSerial mySerial(10,11);

void setup()
{
  Serial.begin(9600); // sets the serial port to 9600
  mySerial.begin(9600); // open the bluetooth serial port
  Serial.println("Gas sensor warming up!");
  Serial.println("Temperature sensor warming up!");
  Serial.println("PM2.5 warming up!");
  delay(10000); // allow the MQ-2 to warm up
   pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output
   pinMode(ledPower, OUTPUT);
   
}

void loop()
{
  sensorValue = analogRead(MQ2pin)-650; // read analog input pin 4
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);	/* Read Temperature */
  temp_val = (temp_adc_val * 0.488);	/* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10);	/* LM35 gives output of 10mv/°C */
  Serial.print("\nTemperature  : ");
  Serial.print(temp_val);
  Serial.print(" °C\n");
    digitalWrite(ledPower, LOW);    // Turn on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);   // Read dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);   // Turn off the LED
  delayMicroseconds(sleepTime);

  // Map 0-5V to 0-1023 integer values and recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // Linear equation derived from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;

  Serial.print("Dust Density: ");
  Serial.print(dustDensity);
  Serial.println(" ug/m3");   // Output in ug/m3

  delay(1000);
  if(sensorValue > (380))
  {
    Serial.print(" | Smoke detected! |");
    tone(buzzer, 10000); // Send 1KHz sound signal...
    delay(1000);         // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);         // ...for 1sec
  }
  
  Serial.println("");
  delay(2000); // wait 2s for next reading
    if(mySerial.available()){
    Serial.println(mySerial.readString()); // send from serial to bluetooth
  }
    if(Serial.available()){
    mySerial.println(Serial.readString()); // send from bluetooth to serial
  }
}