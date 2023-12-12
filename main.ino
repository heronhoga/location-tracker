
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float celc = 0;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  sensors.requestTemperatures();
  celc = sensors.getTempCByIndex(0);
  lcd.setCursor(0,0);
  lcd.print("Wazzup Hoga!");
  lcd.setCursor(0, 1);
  lcd.print("Suhu: " + String(celc));
  delay(1000);
}
