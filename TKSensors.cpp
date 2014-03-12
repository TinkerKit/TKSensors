/**
TKSensors.cpp - High level class to read various TKSensors information

@authors
Arturo Guadalupi <a.guadalupi@arduino.cc>
Angelo Scialabba <a.scialabba@arduino.cc>

May/14/2013

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

#include <TKSensors.h>

extern byte humidityPin = A0;    	// sensore di umidità                            
extern byte analogTempPin = A1;   	//Temperature sensor  
extern byte brightnessPin = A2;    	//Light sensor                        
extern byte CO2Pin = A3;    			//CO2 sensor  

extern byte digitalTempStatus;
extern byte analogTempStatus;
extern byte humidityStatus;
extern byte altitudeStatus;
extern byte CO2Status;
extern byte brightnessStatus;
extern File outputFile;

TKSensors::TKSensors()
{
_twi = &Wire;
_sd = &SD;
}

void TKSensors::begin(){
_twi->begin();
_sd->begin(4);
sensor_config();
enableAll();
}


//Functions to set the analog pin to use for each sensor if the user uses single sensor modules

 void TKSensors::setAnalogTempPin(byte pin)
 {
 analogTempPin = pin;
 }
 
void TKSensors::setHumidityPin(byte pin)
 {
 humidityPin = pin;
 }
 
 void TKSensors::setCO2Pin(byte pin)
 {
   CO2Pin = pin;
 }
 
 void TKSensors::setBrightnessPin(byte pin)
 {
   brightnessPin = pin;
 }
 
//Functions for enabling/disabling each sensor

void TKSensors::analogTempOn()
{
	analogTempStatus = ON;
}

void TKSensors::analogTempOff()
{
	analogTempStatus = OFF;
}

void TKSensors::digitalTempOn()
{
	digitalTempStatus = ON;
}

void TKSensors::digitalTempOff()
{
	digitalTempStatus = OFF;
}

void TKSensors::altitudeOn()
{
	altitudeStatus = ON;
}

void TKSensors::altitudeOff()
{
	altitudeStatus = OFF;
}

void TKSensors::humidityOn()
{
	humidityStatus = ON;
}

void TKSensors::humidityOff()
{
	humidityStatus = OFF;
}

void TKSensors::brightnessOn()
{
	brightnessStatus = ON;
}

void TKSensors::brightnessOff()
{
	brightnessStatus = OFF;
}

void TKSensors::CO2On()
{
	CO2Status = ON;
}

void TKSensors::CO2Off()
{
	CO2Status = OFF;
}

void TKSensors::disableAll()
{
  CO2Status = OFF;
  humidityStatus = OFF;
  brightnessStatus = OFF;
  altitudeStatus = OFF;
  digitalTempStatus = OFF;
  analogTempStatus = OFF;
 }
 
void TKSensors::enableAll()
{
  CO2Status = ON;
  humidityStatus = ON;
  brightnessStatus = ON;
  altitudeStatus = ON;
  digitalTempStatus = ON;
  analogTempStatus = ON;
 }

//Functions to read data from each sensor

byte TKSensors::analogTemp()
{
	if (analogTempStatus) {
    analogTempSaved = analogRead(analogTempPin);
    return analogTempSaved;
	} else return 0;
}

byte TKSensors::humidity()
{
	if (humidityStatus) {
    humiditySaved = analogRead(humidityPin);
    return humiditySaved;
	} else return 0;
}

byte TKSensors::CO2()
{
	if (CO2Status) {
    CO2Saved = analogRead(CO2Pin);
    return CO2Saved;
	} else return 0;
}

byte TKSensors::brightness()
{
	if (brightnessStatus) {
    brightnessSaved = analogRead(brightnessPin);
    return brightnessSaved;
	} else return 0;
}

float TKSensors::digitalTemp(byte Tmode)
{
    if (digitalTempStatus) {
    digitalTempSaved = MLX(Tmode);
	return digitalTempSaved;
	} else return 0;
}

float TKSensors::altitude()	
{

  int m_altitude, c_altitude;
  float l_altitude;
  float f_altitude;

  if (altitudeStatus) {
  m_altitude = twi_Read(0x01);
  c_altitude = twi_Read(0x02);
  l_altitude = (float)(twi_Read(0x03)>>4)/16.0;
  f_altitude = (float)((m_altitude << 8)|c_altitude) + l_altitude;
  

  while(check_new() == false);
  
  return f_altitude;
  } else return 0;
  
}

float TKSensors::digitalTempAlt()
{
  int  m_temp;
  float  l_temp;
  float  f_temperature;

  if (altitudeStatus) {
  m_temp = twi_Read(0x04); //temp, degrees
  l_temp = (float)(twi_Read(0x05)>>4)/16.0; //temp, fraction of a degree
  f_temperature = (float)(m_temp + l_temp);

  while(check_new() == false);
  
  return f_temperature;
  } else return 0;
  
}

//set the file name of the output logfile

void TKSensors::setFilename(const char* filename)
{
  output_filename = filename;    
}

byte TKSensors::logAll(){   //log all the active sensors
  
  outputFile = _sd->open(output_filename, FILE_WRITE);
  if (digitalTempStatus){
    outputFile.print("Temperature (analog) : ");
    outputFile.println(digitalTempSaved);
	
  }
  if (analogTempStatus){
    outputFile.print("Temperature (digital) : ");
    outputFile.println(analogTempSaved);
  }
  if (humidityStatus){
    outputFile.print("Humidity : ");
    outputFile.println(humiditySaved);
  }
  if (altitudeStatus){
    outputFile.print("Altitude : ");
    outputFile.println(altitudeSaved);
  }
  if (CO2Status){
    outputFile.print("CO2 : ");
    outputFile.println(CO2Saved);
  }
  if (brightnessStatus){
    outputFile.print("Brightness : ");
    outputFile.println(brightnessSaved);
  }
  outputFile.println("");
  outputFile.close();
  
}

//*** Functions to log each sensor separately

byte TKSensors::logDigitalTemp(){
  outputFile = _sd->open(output_filename, FILE_WRITE);
  outputFile.print("Temperature (digital) : ");
  outputFile.println(digitalTempSaved);
  outputFile.println("");
  outputFile.close();
}
 
byte TKSensors::logAnalogTemp(){
  outputFile = _sd->open(output_filename, FILE_WRITE);
  outputFile.print("Temperature (analog) : ");
  outputFile.println(analogTempSaved);
  outputFile.println("");
  outputFile.close();
}
byte TKSensors::logHumidity(){
  outputFile = _sd->open(output_filename, FILE_WRITE);
  outputFile.print("Humidity : ");
  outputFile.println(humiditySaved);
  outputFile.println("");
  outputFile.close();
}

byte TKSensors::logAltitude(){
  outputFile = _sd->open(output_filename, FILE_WRITE);
  outputFile.print("Altitude : ");
  outputFile.println(altitudeSaved);
  outputFile.println("");
  outputFile.close();
}

byte TKSensors::logCO2(){
  outputFile = _sd->open(output_filename, FILE_WRITE);
  outputFile.print("CO2 : ");
  outputFile.println(CO2Saved);
  outputFile.println("");
  outputFile.close();
}

byte TKSensors::logBrightness(){
  outputFile = _sd->open(output_filename, FILE_WRITE);
  outputFile.print("Brightness :");
  outputFile.println(brightnessSaved);
  outputFile.println("");
  outputFile.close();
}

byte TKSensors::logDigitalTempAlt(){
  outputFile = _sd->open(output_filename, FILE_WRITE);
  outputFile.print("Temperature (Alt.Sensor) : ");
  outputFile.println(digitalTempSaved); 
  outputFile.println("");
  outputFile.close();
}

//** Low level function to handle sensors

byte TKSensors::twi_Read(byte regAddr)
{
  _twi->beginTransmission(SENSORADDRESS);
  _twi->write(regAddr); // Address of CTRL_REG1
  _twi->endTransmission(false); // Send data to I2C dev with option
  _twi->requestFrom(SENSORADDRESS, 1); // Request the data...
  return _twi->read();
}

void TKSensors::twi_Write(byte regAddr, byte value)
{
  _twi->beginTransmission(SENSORADDRESS);
  _twi->write(regAddr);
  _twi->write(value);
  _twi->endTransmission(true);
}


float TKSensors::MLX(byte wantsFahrenheit){  //reads temperature from  the digital sensor
  
    int dev = 0x5A<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;
    
    _twi->beginTransmission(0x5A);
    _twi->write(0x07);
     _twi->endTransmission(false);

    _twi->requestFrom(0x5A, 3);    // request 6 bytes from slave device #2

    int i = 0;
    char c[] = {0, 0, 0};
    while(_twi->available())    // slave may send less than requested
    { 
    c[i++] = _twi->read();    // receive a byte as character
    }    

    data_low = c[0];
    data_high = c[1];
    pec = c[2];
    
    //This converts high and low bytes together and processes temperature, MSB is a error bit and is ignored for temps
    double tempFactor = 0.02; // 0.02 degrees per LSB (measurement resolution of the MLX90614)
    double tempData = 0x0000; // zero out the data
    int frac; // data past the decimal point
    
    // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;
    
    float celsius = tempData - 273.15;
    float fahrenheit = (celsius*1.8) + 32;
	
	if(wantsFahrenheit) return fahrenheit;
	else return celsius;

}

boolean TKSensors::check_new()
{
  if(twi_Read(0x12) == 0x80) // check INT_SOURCE register on
                             // new data ready (SRC_DRDY)
  {
      return true;
  }
  else return false;
}

void TKSensors::sensor_config()
{
  twi_Write(0x26, 0xB9);
  twi_Write(0x29, 0x80);
  twi_Write(0x13, 0x07);
  twi_Write(0x14, 0xC6);
  twi_Write(0x15, 0x5B);
}
