/*

Arduino Library for Texas Instruments HDC1080 Digital Humidity and Temperature Sensor
Written by AA for ClosedCube
---

The MIT License (MIT)

Copyright (c) 2016-2017 ClosedCube Limited

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <Wire.h>

#include "B4B_HDC1080.h"


B4B_HDC1080::B4B_HDC1080()
{
}

void B4B_HDC1080::begin(uint8_t address, TwoWire* I2C_Bus) {
	_address = address;
	_I2C_Bus = I2C_Bus;

	// Wire.begin(sdata,sclk);

	setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
}

void B4B_HDC1080::setResolution(HDC1080_MeasurementResolution humidity, HDC1080_MeasurementResolution temperature) {
	HDC1080_Registers reg;
	reg.HumidityMeasurementResolution = 0;
	reg.TemperatureMeasurementResolution = 0;

	if (temperature == HDC1080_RESOLUTION_11BIT)
		reg.TemperatureMeasurementResolution = 0x01;

	switch (humidity)
	{
		case HDC1080_RESOLUTION_8BIT:
			reg.HumidityMeasurementResolution = 0x02;
			break;
		case HDC1080_RESOLUTION_11BIT:
			reg.HumidityMeasurementResolution = 0x01;
			break;
		default:
			break;
	}

	writeRegister(reg);
}

HDC1080_SerialNumber B4B_HDC1080::readSerialNumber() {
	HDC1080_SerialNumber sernum;
	sernum.serialFirst = readData(HDC1080_SERIAL_ID_FIRST);
	sernum.serialMid = readData(HDC1080_SERIAL_ID_MID);
	sernum.serialLast = readData(HDC1080_SERIAL_ID_LAST);
	return sernum;
}

HDC1080_Registers B4B_HDC1080::readRegister() {
	HDC1080_Registers reg;
	reg.rawData = (readData(HDC1080_CONFIGURATION) >> 8);
	return reg;
}

void B4B_HDC1080::writeRegister(HDC1080_Registers reg) {
	_I2C_Bus->beginTransmission(_address);
	_I2C_Bus->write(HDC1080_CONFIGURATION);
	_I2C_Bus->write(reg.rawData);
	_I2C_Bus->write(0x00);
	_I2C_Bus->endTransmission();
	delay(10);
}

void B4B_HDC1080::heatUp(uint8_t seconds) {
	HDC1080_Registers reg = readRegister();
	reg.Heater = 1;
	reg.ModeOfAcquisition = 1;
	writeRegister(reg);

	uint8_t buf[4];
	for (int i = 1; i < (seconds*66); i++) {
		_I2C_Bus->beginTransmission(_address);
		_I2C_Bus->write(0x00);
		_I2C_Bus->endTransmission();
		delay(20);
		_I2C_Bus->requestFrom(_address, (uint8_t)4);
		_I2C_Bus->readBytes(buf, (size_t)4);
	}
	reg.Heater = 0;
	reg.ModeOfAcquisition = 0;
	writeRegister(reg);
}


double B4B_HDC1080::readT() {
	return readTemperature();
}

double B4B_HDC1080::readTemperature() {
	uint16_t rawT = readData(HDC1080_TEMPERATURE);
	return (rawT / pow(2, 16)) * 165.0 - 40.0;
}

double B4B_HDC1080::readH() {
	return readHumidity();
}

double B4B_HDC1080::readHumidity() {
	uint16_t rawH = readData(HDC1080_HUMIDITY);
	return (rawH / pow(2, 16)) * 100.0;
}

uint16_t B4B_HDC1080::readManufacturerId() {
	return readData(HDC1080_MANUFACTURER_ID);
}

uint16_t B4B_HDC1080::readDeviceId() {
	return readData(HDC1080_DEVICE_ID);
}

uint16_t B4B_HDC1080::readData(uint8_t pointer) {
	_I2C_Bus->beginTransmission(_address);
	_I2C_Bus->write(pointer);
	_I2C_Bus->endTransmission();
	
	delay(9);
	_I2C_Bus->requestFrom(_address, (uint8_t)2);

	byte msb = _I2C_Bus->read();
	byte lsb = _I2C_Bus->read();

	return msb << 8 | lsb;
}



