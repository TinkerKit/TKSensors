/*
-TKSensors.h -
High level library to read data from 
Tinkerkit! Environmental Shield's sensors.

@authors
Arturo Guadalupi <arturoguadalupi@gmail.com>
Angelo Scialabba <scialabba.angelo@gmail.com>

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


#define SENSORADDRESS  0x60
#define ON 1
#define OFF 0
#define FAHRENHEIT 1
#define CELSIUS 0



class TKSensors{

public:
//**sensor data
 byte digitalTempStatus;
 byte analogTempStatus;
 byte humidityStatus;
 byte altitudeStatus;
 byte CO2Status;
 byte brightnessStatus;
 
 float digitalTempSaved;
 byte analogTempSaved;
 byte humiditySaved;
 float altitudeSaved;
 float digitalTempAltSaved;
 byte CO2Saved;
 byte brightnessSaved;


 byte analogTempPin;
 byte humidityPin;  
 byte CO2Pin;
 byte brightnessPin;
 
 

 TKSensors();
 void begin();
 

//** function for reading sensor values
 byte analogTemp();
 float digitalTemp(byte Tmode);
 byte CO2();
 float altitude();
 float digitalTempAlt();
 byte humidity();
 byte brightness();
 

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
 
//set the sensor pin if the user 
//uses sensor modules
 void setAnalogTempPin(byte pin);
 void setHumidityPin(byte pin);
 void setBrightnessPin(byte pin);
 void setCO2Pin(byte pin);
  
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
