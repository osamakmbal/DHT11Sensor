#include <Dht11Sensor.h>

const int DATA_PIN = 10;

void setup() 
{
  Serial.begin(115200);
  delay ( 1000 ); // wait for 1s to allow the DHT11 to stabilize
}

void loop() 
{
  unsigned long bitStream = 0;
  byte checksum = 0;

  // this should fail with a compiler error because the default ctor is not accessible
  //Dht11Sensor causesCompilerError;

  Dht11Sensor mySensor(DATA_PIN);
  mySensor.refreshMeasurements();
  unsigned int temperature = mySensor.temperature();
  unsigned int humidity = mySensor.humidity();

  Serial.print("Temp in degC: ");
  Serial.println(temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);
  delay ( 5000 );
}

