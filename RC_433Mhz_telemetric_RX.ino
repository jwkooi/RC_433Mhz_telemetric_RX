// *** Jan Willem Kooi
// Telemetric system for RC planes
// Measures air pressure to calculate altitude and battery voltage in RC-plane (TX)
// and sends it via HC-12 (433Mhz) to RC pilot, base station (RX)
// Arduino Nano ATMega328
//
// Transmitter site to put in RC plane
//
// release notes
// 5 mrt 2017: combination HC12 + 20x4 I2C LCD screen
// 23 mrt 2017: added EasyTransfer
// 14 apr 2017: powersupply measuring
// 3 mei 2017: Adding BMP180
// 19 mei 2017: Programming BMP180 groundstation into hight calculation
//
// BMP180 Compiled by Leo Nutz
// www.ALTDuino.de


//*** BMP180
#include <Wire.h>

#define ADDRESS_SENSOR 0x77                 // Sensor address

int16_t  ac1, ac2, ac3, b1, b2, mb, mc, md; // Store sensor PROM values from BMP180
uint16_t ac4, ac5, ac6;                     // Store sensor PROM values from BMP180
// Ultra Low Power       OSS = 0, OSD =  5ms
// Standard              OSS = 1, OSD =  8ms
// High                  OSS = 2, OSD = 14ms
// Ultra High Resolution OSS = 3, OSD = 26ms
const uint8_t oss = 3;                      // Set oversampling setting
const uint8_t osd = 26;                     // with corresponding oversampling delay

int32_t b5;

float T, tBase, pBase;                                 // Set global variables for temperature and pressure


//*** HC12 softwareSerial
#include <SoftwareSerial.h>
SoftwareSerial hc12Serial(2, 3); //RX, TX


//*** LCD 16x2 with I2C
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//*** EasyTranfer
#include <EasyTransfer.h>

EasyTransfer ET;         //create object

struct RECEIVE_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  uint16_t battery = 0;           // battery status in mV
  int32_t temperature = 0;        // airtemperature in celsius
  float pressure = 0;             // pressure in mBar
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE rcData;

int dataReceived = 0;       // counter for data Received (within interval BSvsQ 100% = 36 or 37) 
#define perfectSignal  37   // see above

// *** hardware
#define buttonResetPin 7
#define tonePin 6             //PWM Pin Time0A

//*** Program global variables
boolean pushButton; // pushed = LOW

// Use these for altitude conversions
float p0 = 1010.0;     // Average pressure at sea level (Pa), wordt aangepast door resetknop te drukken
float pOffset = 0.0;  // Difference between BMP180 TX and RX at ground level (reset button)
float pTXcomp = p0;    // 
float altAbs = 0.4, altRel = 0;        // Altitude in meters, Eemnes is 0.40m above sealevel


// RC altitude measuring

float altMax = 0;

// RC battery status

#define lowBatteryAlarm 7.0
float batteryStatus;


//*** Multitasking
unsigned long currentMillis;

unsigned long previousBMP180;               //timers
unsigned long previousDisplayTitles;
unsigned long previousDisplayContent;
unsigned long previousBSvsQ;

int intervalBMP180 = 500;                   // interval in ms
int intervalDisplayTitles = 5000;
int intervalDisplayContent = 1000;
int intervalBSvsQ = 5000;                   // relation with Signal quality. For interval of 5000 the optimum dataReceived is 36 or 37

boolean bSvsQ = true;                       //Toggle Base Station values and Received data quality
