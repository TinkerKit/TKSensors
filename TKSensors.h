/*
-TKSensors.h -
High level library to read data from 
Tinkerkit! Environmental Shield's sensors.

@authors
Arturo Guadalupi <a.guadalupi@arduino.cc>
Angelo Scialabba <a.scialabba@arduino.cc>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

#ifndef TKSensors_h
#define TKSensors_h

#include <inttypes.h>
#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <math.h>

#define SENSORADDRESS  0x60
#define ON 1
#define OFF 0
#define FAHRENHEIT 1
#define CELSIUS 0

#define analogTempSens 0.01

#define VCC	5
#define	N		1024

class TKSensors
{

	public:

	//**sensor data

	byte digitalTempStatus;
	byte analogTempStatus;
	byte humidityStatus;
	byte altitudeStatus;
	byte CO2Status;
	byte brightnessStatus;
 
	float digitalTempSaved;
	float analogTempSaved;
	float humiditySaved;
	float altitudeSaved;
	float digitalTempAltSaved;
	int CO2Saved;
	float brightnessSaved;

	int analogTempPin;
	int humidityPin;  
	int CO2Pin;
	int brightnessPin;
 
	TKSensors();
	void begin();
 
//** function for reading sensor values

	float analogTemp();
	float digitalTemp(byte Tmode);
	int CO2();
	float altitude();
	float digitalTempAlt();
	float humidity();
	float brightness();

//**enable/disable sensors

	void analogTempOn();
	void analogTempOff();

	void digitalTempOn();
	void digitalTempOff();

	void altitudeOn();
	void altitudeOff();

	void humidityOn();
	void humidityOff();

	void CO2On();
	void CO2Off();

	void brightnessOn();
	void brightnessOff();
 
	void disableAll();
	void enableAll();

//****logging functions

	byte logAll();
	byte logAnalogTemp();
	byte logDigitalTemp();
	byte logHumidity();
	byte logAltitude();
	byte logCO2();
	byte logBrightness();
	byte logDigitalTempAlt();
 
//set the sensor pin if the user uses sensor modules

	void setAnalogTempPin(int pin);
	void setHumidityPin(int pin);
	void setBrightnessPin(int pin);
	void setCO2Pin(int pin);
  
	void setFilename(const char* filename);

	private:

	const char* output_filename;
	TwoWire * _twi;
	SDClass * _sd;
	File outputFile;
	float MLX(byte wantsFahrenheit);
	byte twi_Read(byte regAddr);
	void twi_Write(byte regAddr, byte value);
	void sensor_config();
	boolean check_new();
};
#endif 
