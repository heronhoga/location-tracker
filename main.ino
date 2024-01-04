//GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//TEMPERATURE
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


int RXPin = 2;
int TXPin = 3;

int GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);


void setup()
{
  Serial.begin(9600);
  //GPS
  gpsSerial.begin(GPSBaud);

  //LCD
  lcd.init();
  lcd.backlight();

  //TEMPERATURE
  sensors.begin();
}

void loop()
{
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read())) {
      displayInfo();
      delay(5000);
    }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}


void displayInfo()
{
  lcd.setCursor(0, 0);
  lcd.print("DICE-AQ-1");

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if(tempC != DEVICE_DISCONNECTED_C) 
  {

    lcd.setCursor(0, 1);
    lcd.print(tempC);
  } 
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Err read temp");
  }

  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
    Serial.println("Google maps:");
    Serial.print("https://www.google.com/maps/search/?api=1&query=");
    Serial.print(gps.location.lat(), 6); // Print latitude with 6 decimal places
    Serial.print("%2C");
    Serial.println(gps.location.lng(), 6);
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}