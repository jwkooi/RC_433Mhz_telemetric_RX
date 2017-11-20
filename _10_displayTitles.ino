//*** display titles to LCD
void displayTitles() {

  // Altitude
  lcd.setCursor (0, 0);
  lcd.print("Alt: ");
  lcd.setCursor (19, 0);
  lcd.print ("m");


  lcd.setCursor (0, 1);
  lcd.print("Max alt: ");
  lcd.setCursor (19, 1);
  lcd.print ("m");

  // Battery
  lcd.setCursor (0, 3);
  lcd.print("Batt: ");

  lcd.setCursor (14, 3);
  lcd.print (">7.0 V");

}
