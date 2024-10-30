#include <DHT.h>
#include <Ultrasonic.h>

#define ECHOPino 18
#define TRIGPino 5
#define DHTPino 13
#define DOPino 12
#define PIRDPino 17

#define modeloDHT DHT22

DHT dht(DHTPino, modeloDHT);
Ultrasonic ultrasonic(TRIGPino, ECHOPino);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}