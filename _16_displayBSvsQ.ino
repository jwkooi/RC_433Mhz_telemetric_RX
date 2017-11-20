//*** toggle display Base Station pressure and temperature versus Quality of signal
void displayBSvsQ() {

  lcd.setCursor (0, 2);                     // clear line 2 (is third line of LCD display
  lcd.print("                    ");

  if (bSvsQ) {                              // display presure and temperature of base station
    lcd.setCursor (0, 2);
    lcd.print(pBase);
    lcd.print (" mbar");  
    lcd.setCursor (13, 2);
    lcd.print (tBase);
    lcd.print (" C");
  }
  else {
    lcd.setCursor (0, 2);                   // display quality of signal
    if (dataReceived == 0) {
      lcd.print("No signal");
    } else {
      lcd.print ("Signal: ");
      for (int t = 0; t <= dataReceived; t = t + (perfectSignal / 5)) {   // 6 dashes is 100% signal
        lcd.print ("-");
      }
    }
  }

  bSvsQ = !bSvsQ;                       // toggle Base Station values vs Quality of signal

}

