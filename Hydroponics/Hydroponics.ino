#include <Wire.h>
#include <OneWire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <DHT22.h>
#include <DallasTemperature.h>
#include "RTClib.h"
 
// Data wire is plugged into pin 7 on the Arduino
#define DHT22_PIN 7
// Data wire is plugged into pin 4 on the Arduino
#define ONE_WIRE_BUS 4

// Data wire is plugged RX into pin 3 and TX into pin 2 on the Arduino
#define rx 2                  
#define tx 3  

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// LiquidCrystal I2C adress 0x27 
LiquidCrystal_I2C lcd(0x27,  20,  4);

// initial 
RTC_DS1307 rtc;

// initial soft serial 
SoftwareSerial myserial(rx, tx); 
char ph_data[20];
byte received_from_sensor=0; 
float ph=0;

// custom characters
byte water[8] = {
  0b00000,
  0b00100,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110
};

int i = 0;

void setup(void)  {
  Serial.begin(9600);
  myserial.begin(9600);
  sensors.begin();
  Wire.begin();
  rtc.begin();
  lcd.init(); 
  lcd.backlight();
  
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  
  lcd.createChar(0, water);
  
//  rtc.adjust(DateTime(__DATE__, __TIME__));
}
 
 
void loop(void)  {
  check_ph();
  check_dht22();
  check_rtc();
  sensors.requestTemperatures(); 
  
  
  lcd.home();
  lcd.print("Hydropnics");
  lcd.setCursor(0, 1);
  lcd.write(0);
//  lcd.print(sensors.getTempCByIndex(0));
//  lcd.setCursor(0, 2);
//  lcd.print("Temperature = ");
//  lcd.print(myDHT22.getTemperatureC());
//  lcd.setCursor(0, 3);
//  lcd.print("Humidity = ");
//  lcd.print(myDHT22.getHumidity());
//  lcd.print("  pH = ");
//  lcd.print(ph);
  
//  Serial.print("  Button : ");
//  Serial.print(digitalRead(8));
//  Serial.print(digitalRead(9));
//  Serial.print(digitalRead(10));
//  Serial.println(digitalRead(11));
  
//  if(ph >= 3.8)  {
//      Serial.println("OVER");
//  }
 
}

void check_dht22()  {
  DHT22_ERROR_t errorCode;
  errorCode = myDHT22.readData();
  char buf[128];
  sprintf(buf, "Temperature %hi.%01hi C, Humidity %i.%01i %% RH",
          myDHT22.getTemperatureCInt()/10, abs(myDHT22.getTemperatureCInt()%10),
          myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);
}

void check_ph()  {
  if(myserial.available() > 0)  {
    received_from_sensor=myserial.readBytesUntil(13,ph_data,20);
    ph_data[received_from_sensor] = 0;
    ph = atof(ph_data);
  }
}

void check_rtc()  {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}
