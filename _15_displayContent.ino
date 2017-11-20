//*** case 1 lcd screen
void displayContent() {

  lcd.setCursor (9, 0);
  lcd.print ("         ");  //clear lcd field
  lcd.setCursor (9, 0);
  lcd.print (altRel);

  //*** Max altitude
  lcd.setCursor (9, 1);
  lcd.print ("         ");  // clear lcd field
  lcd.setCursor (9, 1);
  lcd.print (altMax);


  //*** Battery
  lcd.setCursor (6, 3);
  lcd.print ("        "); // clear lcd field
  lcd.setCursor (6, 3);
  lcd.print (batteryStatus);

  if (batteryStatus < lowBatteryAlarm) {  // Blink for alarm low battery
    lcd.setCursor (5, 3);
    lcd.blink();
  } else {
    lcd.setCursor (5, 3);
    lcd.noBlink();
  }


}
