void setup() {
  Serial.begin(9600);

  //*** BMP180
  Wire.begin();                             // Activate I2C for BMP180

  init_SENSOR();                            // Initialize baro sensor variables
  delay(100);


  //*** HC-12 software serial port
  hc12Serial.begin(9600);

  //*** LCD
  lcd.begin(20, 4);  // initialize the lcd for 16 chars 2 lines

  //Blink backlight and clear
  lcd.backlight();
  delay(100);
  lcd.noBacklight();
  delay(100);
  lcd.backlight(); // finish with backlight on
  lcd.clear();

  //*** EasyTransfer
  ET.begin(details(rcData), &hc12Serial);

  //*** Hardware
  pinMode(buttonResetPin, INPUT); // open == HIGH

  //*** display titles
  displayTitles();

}
