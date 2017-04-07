



/*************************************************** 
  This is an example for the Adafruit Thermocouple Sensor w/MAX31855K

  Designed specifically to work with the Adafruit Thermocouple Sensor
  ----> https://www.adafruit.com/products/269

  These displays use SPI to communicate, 3 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <ShiftedLCD.h>
//#include <Time.h>
//#include <TimeLib.h>
#include <StopWatch.h>


// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define MAXDO   2
#define MAXCS   3
#define MAXCLK  4

// Initialize the Thermocouple
Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9);

//Global Variables
StopWatch sw_millis;    // MILLIS (default)
StopWatch sw_micros(StopWatch::MICROS);
StopWatch sw_secs(StopWatch::SECONDS);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


void setup() {
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  lcd.clear();
  lcd.print("Coffee Roaster");
  // wait for MAX chip to stabilize
  delay(1000);
  lcd.clear();
//prepare timer variables
  sw_millis.start();
  sw_micros.start();
  sw_secs.start();
}

void loop() {
  // basic readout test, just print the current temp
   Serial.print("Int. Temp = ");
   Serial.println(thermocouple.readInternal());
 
   //Timer Display
   lcd.setCursor (8, 0);
   lcd.print("TM ");
   
   lcd.setCursor (11, 0);
   if (sw_secs.elapsed()<10)
   {
   lcd.setCursor (11, 0);
   lcd.print("MM:0");
   lcd.setCursor (15, 0);
   lcd.print(sw_secs.elapsed());
   }
   else if (sw_secs.elapsed()<61)
   {
   lcd.setCursor (11, 0);
   lcd.print("MM:");
   lcd.setCursor (14, 0);
   lcd.print(sw_secs.elapsed());
   }
   else
   {
   sw_secs.reset();
   sw_secs.start();
   lcd.print(sw_secs.elapsed());
   }
   
   //Bean Temperature measurement and display
   double bt = thermocouple.readFarenheit(); 
   lcd.setCursor(0, 1);
   if (isnan(bt)) 
   {
     lcd.print("BT "); 
     lcd.print("err");
   } 
   else 
   {
     lcd.print("BT "); 
     lcd.print(round(bt));
     lcd.print(" ");
     Serial.print("Bean Temp = *");
     Serial.println(bt);
   }
   
   //Air Temperature measurement and display
   double at = thermocouple.readFarenheit(); 
   lcd.setCursor(0, 0);
   if (isnan(at)) 
   {
   lcd.print("AT "); 
   lcd.print("err");
   } 
   else 
   {
     lcd.print("AT "); 
     lcd.print(round(at));
     lcd.print(" ");
     Serial.print("Air Temp = *");
     Serial.println(at);
   }
   
   //Fan Speed measurement and display
   lcd.setCursor(8, 1);
   lcd.print("FS  100%");

//end of loop delay
   delay(1000);

}
