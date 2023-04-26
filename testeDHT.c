#include "DHT.h"
DHT dht (13,DHT11);
int temp = 0;
int umid = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  temp = dht.readTemperature();
  umid = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("        Umidade:");
  Serial.println(umid);
  delay(1000);
}