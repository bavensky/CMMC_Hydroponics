#include <Wire.h>
#include <OneWire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <DHT22.h>
#include <DallasTemperature.h>
#include "RTClib.h"
 
#define EEPROM_PUMP  9
// Data wire is plugged into pin 7 on the Arduino
#define DHT22_PIN 7

// Data wire is plugged into pin 4 on the Arduino
#define ONE_WIRE_BUS 4

// Data wire is plugged RX into pin 3 and TX into pin 2 on the Arduino
#define rx 2                  
#define tx 3  

// define pin setup
#define  MENU    8
#define  SELECT  9
#define  UP      10
#define  DOWN    11

#define DEBOUNCE 200

unsigned int loop_menu = 0;
unsigned int select_menu = 1;

// Pump water pin 5
#define pump 5
int speedwater = 255;

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

//  initial Variable
int i = 0;
int _year,  _month,  _day;
int _hour,  _minute,  _second;

// custom characters
byte temp[8] = {
  0b00000,
  0b00100,
  0b00100,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110
};

byte humi[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01110
};

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

byte celsius[8] = {
  0b01110,
  0b10001,
  0b10001,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte ph_emo[8] = {
  0b00000,
  0b01110,
  0b01001,
  0b01001,
  0b01110,
  0b01000,
  0b01000,
  0b01000
};

byte turnleft[8] = {
  0b11000,
  0b01100,
  0b00110,
  0b00011,
  0b00110,
  0b01100,
  0b11000,
  0b00000
};

//byte water[8] = {
//  0b00000,
//  0b00100,
//  0b00100,
//  0b01110,
//  0b11111,
//  0b11111,
//  0b11111,
//  0b01110
//};
//
//byte water[8] = {
//  0b00000,
//  0b00100,
//  0b00100,
//  0b01110,
//  0b11111,
//  0b11111,
//  0b11111,
//  0b01110
//};

void setup(void)  {
  Serial.begin(9600);
  myserial.begin(9600);
  sensors.begin();
  Wire.begin();
  rtc.begin();
  lcd.init(); 
  lcd.backlight();
  
  pinMode(MENU, INPUT_PULLUP);
  pinMode(SELECT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  
  lcd.createChar(0, celsius);
  lcd.createChar(1, water);
  lcd.createChar(2, ph_emo);
  lcd.createChar(3, turnleft);
//  lcd.createChar(4, water);
//  lcd.createChar(5, water);
//  lcd.createChar(6, water);
//  lcd.createChar(7, water);
  
//  rtc.adjust(DateTime(__DATE__, __TIME__));
  analogWrite(pump,  255);
}
 
void loop(void)  {
  check_ph();
  check_dht22();
  sensors.requestTemperatures(); 
  check_rtc();

  display_main();

  control_pump();
  analogWrite(pump,  speedwater);
  
//  Serial.print(speedwater);
//  Serial.println(EEPROM.read(EEPROM_PUMP));
}
