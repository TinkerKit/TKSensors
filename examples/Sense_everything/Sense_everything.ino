/*
ThinkerKit Environmental Shield.
 
 Arturo Guadalupi <arturoguadalupi@gmail.com>
 Angelo Scialabba <scialabba.angelo@gmail.com>
 */
/****************************************/

#include <Wire.h> //Remember to include Wire.h and SD.h together with TKSensors.h
#include <SD.h>
#include <TKSensors.h>
#include <SPI.h>

TKSensors Envi = TKSensors();
/*In order to save files on SD use a file name that have a max of 8 chars
 example "12345678.txt"
 
 Longer file name are not allowed, so if the sketch doesn't work check it twice*/

void setup()
{
  Envi.begin();
  Envi.setFilename("senslog.txt"); //create file on SD
  
  Serial.begin(115200);//Serial start
}

void loop()
{
  /*If you don't have an Environmental Shield, but individual sensors,
   you can set pin of analog sesnsors using the functions:
   void setTempPin(int pin);
   void setHumidityPin(int pin);
   void setBrightnessPin(int pin);
   void setCO2Pin(int pin);
   */

  //Get and print sensor values individually
  Serial.println("##########    One by One    ##########");

  //enable analog temperature sensor
  Envi.analogTempOn(); 
  //print 
  Serial.print("Temperature (analog):\t");
  Serial.print(Envi.analogTemp());
  Serial.println(" C");
  //save on SD;
  Envi.logAnalogTemp(); 
  //disable analog temperature sensor
  Envi.analogTempOff(); 

  //enable digital temperature sensor
  Envi.digitalTempOn();
  //print 
  Serial.print("Temperature (digital):\t");
  Serial.print (Envi.digitalTemp(CELSIUS));
  Serial.println (" C");
  Serial.print("Temperature (digital):\t");
  Serial.print (Envi.digitalTemp(FAHRENHEIT));
  Serial.println (" F");
  //save on SD
  Envi.logDigitalTemp(); 
  //disable digital temperature sensor
  Envi.digitalTempOff(); 

  //enable altitude sensor
  Envi.altitudeOn(); 
  //print
  Serial.print("Altitude:\t\t");
  Serial.print (Envi.altitude());
  Serial.println (" m");
  //save on SD
  Envi.logAltitude(); 
  //altitude sensor can also read temperature
  Serial.print("Temperature (altitude):\t");
  Serial.print(Envi.digitalTempAlt());
  Serial.println (" C");
  //save on SD
  Envi.logDigitalTempAlt();
  //disable altitude sensor
  Envi.altitudeOff(); 

  //enable humidity sensor
  Envi.humidityOn(); 
  //print
  Serial.print ("Humidity:\t\t");
  Serial.print (Envi.humidity());
  Serial.println("%");
  //save on SD
  Envi.logHumidity(); 
  //disable humidity sensor
  Envi.humidityOff(); 

  //enable CO2 sensor
  Envi.CO2On(); 
  //print
  Serial.print ("CO2:\t\t\t");
  Serial.println (Envi.CO2());
  //save on SD
  Envi.logCO2(); 
  //disable CO2 sensor
  Envi.CO2Off(); 

  //enable brightness sensor
  Envi.brightnessOn(); 
  //print
  Serial.print ("Brightness:\t\t");
  Serial.println (Envi.brightness());
  //save on SD
  Envi.logBrightness(); 
  //disable CO2 sensor
  Envi.brightnessOff(); 

  Serial.println();

  delay(3000);

  //if you need all the values, you can enable
  //and disable all sensors with:
  Envi.enableAll(); 
  Serial.println("##########    All together    ##########");

  //print values
  Serial.print("Temperature (analog):\t");
  Serial.print(Envi.analogTemp());
  Serial.println("°C");
  
  Serial.print("Temperature (digital):\t");
  Serial.print (Envi.digitalTemp(CELSIUS));
  Serial.println (" C");
  
  Serial.print("Temperature (digital):\t");
  Serial.print (Envi.digitalTemp(FAHRENHEIT));
  Serial.println (" F");
  
  Serial.print ("Altitude:\t\t");
  Serial.print (Envi.altitude());
  Serial.println (" m");
  
  Serial.print("Temperature (altitude):\t");
  Serial.print (Envi.digitalTempAlt());
  Serial.println (" C");
  
  Serial.print ("Humidity:\t\t");
  Serial.print (Envi.humidity());
  Serial.println("%");
  
  Serial.print ("CO2:\t\t\t");
  Serial.println (Envi.CO2());
  Serial.print ("Brightness:\t\t");
  Serial.println (Envi.brightness());

  //save data from all sensors on SD
  Envi.logAll(); 

  //disable all sensors
  Envi.disableAll(); 

  Serial.println();

  delay(3000);
}