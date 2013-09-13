/*
ThinkerKit Environmental Shield.

Arturo Guadalupi <arturoguadalupi@gmail.com>
Angelo Scialabba <scialabba.angelo@gmail.com>
*/
/****************************************/

#include <Wire.h> //Remember to include Wire.h and SD.h together with TKSensors.h
#include <SD.h>
#include <TKSensors.h>

TKSensors Envi = TKSensors();
/*In order to save files on SD use a file name that have a max of 8 chars
example "12345678.txt"

Longer file name are not allowed, so if the sketch doesn't work check it twice*/

void setup()
{
  Envi.begin();
  Envi.setFilename("senslog.txt"); //create file on SD
 
}

void loop()
{
 /*If you don't have an Environmental Shield, but individual sensors,
 you can set pin of analog sesnsors using the functions:
 void setTempPin(byte pin);
 void setHumidityPin(byte pin);
 void setBrightnessPin(byte pin);
 void setCO2Pin(byte pin);
 */
 Serial.println("1 by 1");
 
 Envi.analogTempOn(); //enable analog temperature sensor
 Serial.print("Temperature (analog) :  ");
 Serial.println (Envi.analogTemp());
 Envi.logAnalogTemp(); //save on SD;
 Envi.analogTempOff(); //disable analog temperature sensor
 
 Envi.digitalTempOn(); //enable digital temperature sensor
 Serial.print("Temperature (digital) :  ");
 Serial.print (Envi.digitalTemp());
 Serial.println ("Celsius degrees");
 Serial.print("Temperature (digital) :  ");
 Envi.digitalTemp(FAHRENHEIT);
 Serial.print (Envi.digitalTemp());
 Serial.println ("Fahrenheit degrees");
 Envi.logDigitalTemp(); //save on SD;
 Envi.digitalTempOff(); //disable digital temperature sensor
 
 //altitude also offering a temperature value
 Envi.altitudeOn(); //enable altitude sensor
 Serial.print("Altitude :  ");
 Serial.println (Envi.altitude());
 Envi.logAltitude(); //save on SD;
 Serial.print("Temperature (from altitude sensors) :  ");
 Serial.print(Envi.digitalTempAlt());
 Serial.println ("Celsius degrees");
 Envi.logDigitalTempAlt();
 Envi.altitudeOff(); //disable altitude sensor

 Envi.humidityOn(); //enable humidity sensor
 Serial.print ("Humidity :  ");
 Serial.println (Envi.humidity());
 Envi.logHumidity(); //save on SD;
 Envi.humidityOff(); //disable humidity sensor
 
 Envi.CO2On(); //enable CO2 sensor
 Serial.print ("CO2 :  ");
 Serial.println (Envi.CO2());
 Envi.logCO2(); //save on SD;
 Envi.CO2Off(); //disable CO2 sensor
 
 Envi.brightnessOn(); //enable brightness sensor
 Serial.print ("Brightness :  ");
 Serial.println (Envi.brightness());
 Envi.logBrightness(); //save on SD;
 Envi.brightnessOff(); //disable CO2 sensor
 
 Serial.println(" ");
 Serial.println(" ");
 Serial.println(" ");
 
 delay(3000);
 Serial.println("Enable all sensors");
 Envi.enableAll(); //enable all sensors on shield
 
 Envi.refreshData(); //get new data from sensors;
 Serial.print("Temperature (analog) :  ");
 Serial.println (Envi.analogTempValue);
 Serial.print("Temperature (digital) :  ");
 Serial.print (Envi.digitalTempValue);
 Serial.println ("Celsius degrees");
 Serial.print("Altitude :  ");
 Serial.println (Envi.altitudeValue);
 Serial.print ("Humidity :  ");
 Serial.println (Envi.humidityValue);
 Serial.print ("CO2 :  ");
 Serial.println (Envi.CO2Value);
 Serial.print ("Brightness :  ");
 Serial.println (Envi.brightnessValue);
 Envi.logAll(); //save data from all sensors on SD

 Serial.println(" ");
 Serial.println(" ");
 Serial.println(" ");
 
 delay(3000);
 Serial.println("Disable all sensors");
 Envi.disableAll(); //disable all sensors
 Envi.refreshData();
 Serial.print("Temperature (analog) :  ");
 Serial.println (Envi.analogTempValue);
 Serial.print("Temperature (digital) :  ");
 Serial.print (Envi.digitalTempValue);
 Serial.println ("Celsius degrees");
 Serial.print("Altitude :  ");
 Serial.println (Envi.altitudeValue);
 Serial.print ("Humidity :  ");
 Serial.println (Envi.humidityValue);
 Serial.print ("CO2 :  ");
 Serial.println (Envi.CO2Value);
 Serial.print ("Brightness :  ");
 Serial.println (Envi.brightnessValue);
 Serial.println(" ");
 Serial.println(" ");
 Serial.println(" ");
 
 delay(3000);
}
