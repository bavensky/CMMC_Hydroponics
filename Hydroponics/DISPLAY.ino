//////////////////////////    Display    //////////////////////////
void display_main()  {
  lcd.home();
  lcd.print(" Hydropnics Systems ");
  
  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.print(myDHT22.getTemperatureC());
  lcd.write(0);
  lcd.print("C ");
  lcd.print(myDHT22.getHumidity());
  lcd.print(" %RH  ");
  
  lcd.setCursor(0, 2);
  lcd.print(" ");
  lcd.write(1);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print("   ");
  lcd.write(2);
  lcd.print("H ");
  lcd.print(ph);
  lcd.print("    ");
  
  lcd.setCursor(0, 3);
  lcd.print("   Time ");
  if(_hour <= 10){  lcd.print("0");  }
  lcd.print(_hour);
  lcd.print(":");
  if(_minute <= 10){  lcd.print("0");  }
  lcd.print(_minute);
  lcd.print(":");
  if(_second <= 10){  lcd.print("0");  }
  lcd.print(_second);
  lcd.print("    ");
  
}
