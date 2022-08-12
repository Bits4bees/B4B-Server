/**************************************************************************************

This is example for ClosedCube HDC1080 Humidity and Temperature Sensor breakout booard

Initial Date: 07-Jun-2017

Hardware connections for Arduino Uno:
VDD to 3.3V DC
SCL to A5
SDA to A4
GND to common ground

Written by AA for ClosedCube

MIT License

**************************************************************************************/

#include <Wire.h>
#include "ClosedCube_HDC1080.h"

ClosedCube_HDC1080 sensor01;
#define ADD1 0x40
#define SDA1 23
#define SCL1 22

ClosedCube_HDC1080 sensor02;
#define ADD2 0x40
#define SDA2 33
#define SCL2 32

void setup()
{
	Serial.begin(9600);
  Serial.println('\n');
	Serial.println("ClosedCube HDC1080 Measurement Resolutions Arduino Test");
  delay(1000);

	sensor01.begin(ADD1,SDA1,SCL1);
  sensor02.begin(ADD2,SDA2,SCL2);

//	Serial.print("Manufacturer ID=0x");
//	Serial.println(sensor01.readManufacturerId(), HEX); // 0x5449 ID of Texas Instruments
//	Serial.print("Device ID=0x");
//	Serial.println(sensor01.readDeviceId(), HEX); // 0x1050 ID of the device

  sensor01.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
  sensor02.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
  delay(2000);
}

void loop()
{	
  Serial.print("T=");
  Serial.print(sensor01.readTemperature());
  Serial.print("C, RH=");
  Serial.print(sensor01.readHumidity());
  Serial.print("% ");
  Serial.print(" T=");
  Serial.print(sensor02.readTemperature());
  Serial.print("C, RH=");
  Serial.print(sensor02.readHumidity());
  Serial.println("%");
  delay(1000);
}
