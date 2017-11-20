void varioMeter() {
  int ddsAcc;
  float toneFreq, toneFreqLowpass, flpressure, lowpassFast, lowpassSlow ;

  lowpassFast =   rcData.pressure - pOffset;
  lowpassSlow = flpressure = lowpassFast; //setup start values

  flpressure = rcData.pressure - pOffset;                      // pressure of RC plane (TX) parsed

  lowpassFast = lowpassFast + (flpressure - lowpassFast) * 0.3;
  lowpassSlow = lowpassSlow + (flpressure - lowpassSlow) * 0.15;
  toneFreq = (lowpassSlow - lowpassFast) * 50;
  toneFreqLowpass = toneFreqLowpass + (toneFreq - toneFreqLowpass) * 0.1;
  toneFreq = constrain(toneFreqLowpass, -1000, 1000);
  ddsAcc += toneFreq * 100 + 2000;

  if (toneFreq > 0 && ddsAcc > 0)
  {
    tone(2, toneFreq + 510);

  }
  else
  {
    noTone(2);

  }

}

