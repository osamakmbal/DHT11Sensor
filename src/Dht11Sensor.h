//------------------------------------------------------
// Dht11Sensor.h
//
// based on info from DHT11 datasheet available at: http://www.micro4you.com/files/sensor/DHT11.pdf

// #pragma once
#ifndef DHT11SENSOR_H
#define DHT11SENSOR_H

class Dht11Sensor
{
  private:
    Dht11Sensor ( );
    unsigned int _temperature;
    unsigned int _humidity;
    byte _dataPin;

  public:
    Dht11Sensor ( byte dataPin );

    boolean refreshMeasurements ( );
    unsigned int temperature();
    unsigned int humidity();
};

#endif
