//////////////////////////    Control Pump    //////////////////////////
void control_pump()  {
  if(loop_menu >= 2)  {
    loop_menu = 0;
  }
  
  if(digitalRead(MENU)  == 0)  {
    delay(DEBOUNCE);
    loop_menu ++;
    analogWrite(pump,  255);
    lcd.clear();
  }
  
  // loop menu set speed pump and temperature
  while(loop_menu == 1)  {
    if(digitalRead(UP)  == 0)  {  select_menu ++;  lcd.clear();  }
    if(digitalRead(DOWN)  == 0)  {  select_menu --;  lcd.clear();  }
    
    if(select_menu <= 0)  {  select_menu = 1;  }
    if(select_menu >= 3)  {  select_menu = 2;  }
    
    if(digitalRead(SELECT) == 0 && select_menu == 1 )  {  lcd.clear(); mode1();  }
    if(digitalRead(SELECT) == 0 && select_menu == 2 )  {  lcd.clear(); mode2();  }
    
    if(digitalRead(MENU) == 0)  {
      delay(DEBOUNCE);
      loop_menu = 0;
    }
    
    lcd.home();
    lcd.print("Menu :              ");

    if(select_menu == 1)  {
      lcd.setCursor(0, 1); 
      lcd.write(3); 
      lcd.print(" Set Speed Pump    ");  
     
      lcd.setCursor(0, 2);
      lcd.print("  Set Temperature  ");  
    }

    if(select_menu == 2)  {
      lcd.setCursor(0, 1); 
      lcd.print("  Set Speed Pump  ");  
      
      lcd.setCursor(0, 2);
      lcd.write(3);
      lcd.print(" Set Temperature  ");  
    }   
    

  }  // END loop menu
  
}

//  Set speed pump
void mode1()  {
  while(1)  {
    lcd.home();  
    lcd.print(" Set Speed Pump");
    lcd.setCursor(0,  1);
    lcd.print("  Speed = ");
    lcd.print(map(speedwater,  255,  0,  0,  10));
    lcd.print("  ");
    
    if(speedwater >= 255)  {  speedwater = 255;  }
    if(speedwater <= 0)  {  speedwater = 0;  }
    if(digitalRead(UP) == 0)  { delay(DEBOUNCE);  speedwater -= 15;  }
    if(digitalRead(DOWN) == 0)  { delay(DEBOUNCE);  speedwater += 15;   }
    if(digitalRead(MENU) == 0)  { delay(DEBOUNCE);  break; }
    
    EEPROM.write(EEPROM_PUMP,  speedwater);
  }
}

//  Set  temperature
void mode2()  {
  while(1)  {
    lcd.home();  
    lcd.print(" Set Temperature");
    if(digitalRead(MENU) == 0)  { delay(DEBOUNCE); break; }
  }
}
