//////////////////////////    Check Sensor    //////////////////////////
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
  _year  =  now.year();
  _month  =  now.month();
  _day  =  now.day();
  _hour  =  now.hour();
  _minute  =  now.minute();
  _second  =  now.second();

//    Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(' ');
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();
}
