#include <DHT22.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
 
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

// initial soft serial 
SoftwareSerial myserial(rx, tx); 
char ph_data[20];
byte received_from_sensor=0; 
float ph=0;


void setup(void)  {
  Serial.begin(9600);
  myserial.begin(9600);
  sensors.begin();
  
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
}
 
 
void loop(void)  {
  check_ph();
  check_dht22();
  sensors.requestTemperatures(); 

  Serial.print("Device is : ");
  Serial.print("DS18B20 = ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("  Temperature = ");
  Serial.print(myDHT22.getTemperatureC());
  Serial.print("  Humidity = ");
  Serial.print(myDHT22.getHumidity());
  Serial.print("  pH = ");
  Serial.print(ph);
  
  Serial.print("  Button : ");
  Serial.print(digitalRead(8));
  Serial.print(digitalRead(9));
  Serial.print(digitalRead(10));
  Serial.println(digitalRead(11));
  
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
