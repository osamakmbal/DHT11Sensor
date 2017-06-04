//------------------------------------------------------
// Dht11Sensor.cpp

#include "Arduino.h"
#include "Dht11Sensor.h"

Dht11Sensor::Dht11Sensor()
{
  // don't allow creation of this type without specifying a dataPin
}

Dht11Sensor::Dht11Sensor( byte dataPin )
{
  _dataPin = dataPin;
}

unsigned int Dht11Sensor::temperature()
{
  return _temperature;
}

unsigned int Dht11Sensor::humidity()
{
  return _humidity;
}

boolean Dht11Sensor::refreshMeasurements()
{
  boolean readSucceeded = false;

  unsigned long bitStream = 0;
  byte checksum = 0;
  int pulseDurationMicroseconds = 0;
  //-----------------------------------------------
  // signal DHT11 to transition into active mode (low 18ms, high 40us)
  

  pinMode ( _dataPin, OUTPUT );
  
  // 1. pull signal voltage down for at least 18ms
  digitalWrite ( _dataPin, LOW );
  delayMicroseconds ( 18500 );
  
  // 2. pull up signal voltage for 20-40us
  digitalWrite ( _dataPin, HIGH );
  delayMicroseconds ( 40 );

  //-----------------------------------------------
  // wait for DHT to signal that it has entered transmit mode (low 80us, high 80us)
  pinMode ( _dataPin, INPUT );

  pulseDurationMicroseconds = pulseIn ( _dataPin, HIGH );
  if ( pulseDurationMicroseconds > 0 )
  {
    // each data bit is encoded as a pulse with:
    // 1. low for 50us
    // 2. high for some t, where:
    //      26us < t < 28us means a '0' bit
    //      t = 70us means a '1' bit

    // read sensor data
    for (int i = 0; i < 32; i++)
    {
      // shift previously read bits left 1 bit
      bitStream = bitStream << 1;

      // read data signal from DHT
      pulseDurationMicroseconds = pulseIn ( _dataPin, HIGH );
      if ( pulseDurationMicroseconds > 40 )
      {
        bitStream |= 1;
      }
    }

    // read checksum
    for (int i = 0; i < 8; i++)
    {
      // shift previously read bits left 1 bit
      checksum = checksum << 1;

      // read data signal from DHT
      pulseDurationMicroseconds = pulseIn ( _dataPin, HIGH );
      if ( pulseDurationMicroseconds > 40 )
      {
        checksum |= 1;
      }      
    }

    _temperature = ( bitStream & 0x0000FF00 ) >> 8;
    _humidity = bitStream >> 24;

    if ( ( _temperature + _humidity ) == checksum )
    {
      readSucceeded = true;
    }

#ifdef DEBUG
    Serial.print("Data bits: ");
    Serial.println(bitStream, HEX);
    Serial.println(bitStream, BIN);
    
    Serial.print("Checksum value: ");
    Serial.println(checksum, HEX);
#endif
  }

  return readSucceeded;
}
