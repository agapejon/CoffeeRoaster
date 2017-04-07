
/*************************************************** 
This sketch is for a custom coffee roaster.

Created by Jonathan Dowell
 ****************************************************/
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MAX31855.h"
#include <ShiftedLCD.h>
#include <StopWatch.h>


// thermocouple instanace 1
#define MAX1DO   2
#define MAX1CS   3
#define MAX1CLK  4

// thermocouple instanace 2
#define MAX2DO   5
#define MAX2CS   6
#define MAX2CLK  7

// Initialize the Thermocouples
Adafruit_MAX31855 thermocouple1(MAX1CLK, MAX1CS, MAX1DO);
Adafruit_MAX31855 thermocouple2(MAX2CLK, MAX2CS, MAX2DO);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9);

//Global Variables
StopWatch sw_millis;    // MILLIS (default)
StopWatch sw_micros(StopWatch::MICROS);
StopWatch sw_secs(StopWatch::SECONDS);
StopWatch sw_mins(StopWatch::SECONDS);

void setup() {
  Serial.begin(9600);

// set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Loving Coffee");
  lcd.setCursor (0, 1);
  lcd.print("Loving People");
  ;
// wait for MAX chip to stabilize
  delay(2000);
  lcd.clear();
  
//prepare timer variables
  sw_secs.start();
  sw_mins.start();
}

void loop() {
  // basic readout test, just print the current temp
  // Serial.print("Int. Temp = ");
  // Serial.println(thermocouple.readInternal());
 
   //Timer Display
   lcd.setCursor (8, 0);
   lcd.print("TM ");

   //timer minutes display
   if (sw_mins.elapsed()<60)
   {
      lcd.setCursor (11, 0);
      lcd.print("00:");
   }
    else if (sw_mins.elapsed()<600)
    {
      lcd.setCursor (11, 0);
      lcd.print("0");
      lcd.setCursor (12, 0);
      lcd.print(round(sw_mins.elapsed()/60));
      lcd.setCursor (13, 0);
      lcd.print(":");
      }
    else 
    {
      lcd.setCursor (11, 0);
      lcd.print(round(sw_mins.elapsed()/60));   
      }
  
   
   //Timer seconds display
   if (sw_secs.elapsed()<10)
   {
      lcd.setCursor (14, 0);
      lcd.print("0");
      lcd.setCursor (15, 0);
      lcd.print(round(sw_secs.elapsed()));
   }
   else if (sw_secs.elapsed()<60)
   {
      lcd.setCursor (14, 0);
      lcd.print(round(sw_secs.elapsed()));
   }
   else
   {
      sw_secs.reset();
      sw_secs.start();
      lcd.setCursor (14, 0);
      lcd.print("0");
      lcd.setCursor (15, 0);
      lcd.print(round(sw_secs.elapsed()));
   }
   
   //Bean Temperature measurement and display
   double bt = thermocouple1.readFarenheit(); 
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
   double at = thermocouple2.readFarenheit(); 
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
   delay(100);

}
