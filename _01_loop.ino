void loop() {
  currentMillis = millis();

  //*** Data received from TX?
  if (ET.receiveData()) {
    dataReceived = dataReceived + 1;              // data is received, should be 36 or 37 is signal is optimal
  }

  //***  buttonReset pressed?
  if (digitalRead(buttonResetPin) == LOW) {        // set altitude to zero and set offset between BMP180 TX and RX
    pOffset = rcData.pressure - pBase;
    p0 = pBase;
    altMax = 0;
  }


  //*** BMP180 groundstation RX
  if (currentMillis - previousBMP180 >= intervalBMP180) {  //Only excecute every interval
    previousBMP180 = currentMillis;                        // reset and wait interval time

    b5 = temperature();         // Read and calculate temperature (T) b5 is not the temperature
    tBase = T;
    pBase = pressure(b5);       // Read and calculate pressure (P) at RX (base station)
  }

  if (dataReceived > 0) {
    altRel = (float)44330 * (1 - pow(((float) (rcData.pressure - pOffset) / p0), 0.190295)); //altitude calculation

    if (altRel > altMax) {        // set maximum altitude
      altMax = altRel;
    }

    //*** Battery calculation
    batteryStatus = (rcData.battery * (5.0 / 1023.0)) * 2;
  }

  //*** display titles
  if (currentMillis - previousDisplayTitles >= intervalDisplayTitles) {      // Only excecute every interval
    previousDisplayTitles = currentMillis;                                   // reset and wait interval time

    displayTitles();  //print framework of titles to LCD screen
  }

  //*** display content
  if (currentMillis - previousDisplayContent >= intervalDisplayContent) {     // Only excecute every interval
    previousDisplayContent = currentMillis;                                   // reset and wait interval time

    displayContent();
  }


  //*** Toggle Base Station values / quality of signal
  if (currentMillis - previousBSvsQ >= intervalBSvsQ) {                      // Only excecute every interval
    previousBSvsQ = currentMillis;                                           // reset and wait interval time
    displayBSvsQ();                                                          // display on LCD   
    dataReceived = 0;                                                        // reset count of packages received   
  }
}


