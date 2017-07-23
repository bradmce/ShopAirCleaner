#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

int pos0=0;
int pos1=0;
int colon=1;
int pos3=0;
int pos4=0;
int hours = 0; // start hours
int minutes = 0; //start min
int seconds = 0; //start seconds

 
void setup() {
  #ifndef __AVR_ATtiny85__
    Serial.begin(9600);
    Serial.println("7 Segment Backpack Test");
  #endif
  matrix.begin(0x70);
  WriteOFF();
}
void WriteOFF()  {   //  Only draw "_OFF" to the 7-segment display, no mode or relay changes included here
  matrix.setBrightness(0);  //  dim the brightness while in OFF mode
  matrix.writeDigitRaw(0,0x0);  //  blank pixel
  matrix.writeDigitNum(1,0); // zero
  matrix.drawColon(false);  //  Turn off the colon
  matrix.writeDigitRaw(3,0x71);   // Hex map for letter F
  matrix.writeDigitRaw(4,0x71);   // Hex map for letter F
  matrix.writeDisplay();
}
void WriteTime() {
  matrix.setBrightness(5);
  matrix.writeDigitNum(0,pos0);
  matrix.writeDigitNum(1,pos1);
  if (colon==1) {     //toggle the colon depending on input
    matrix.drawColon(true);
  } else {
    matrix.drawColon(false);
  }
  matrix.writeDigitNum(3,pos3);
  matrix.writeDigitNum(4,pos4);    
  matrix.writeDisplay();
}

void loop() {
  if (irrecv.decode(&results)) // have we received an IR signal?








  
  delay(2000);
  //  simulate press of # button on IR remote
    pos0=0;pos1=0;colon=1;pos3=0;pos4=0;
    hours=0;minutes=0;seconds=0;
    WriteTime();
    delay(250);
  //  simulate press of 1 button on IR remote
    pos0=0;pos1=0;colon=1;pos3=0;pos4=1;
    hours=0;minutes=0;seconds=0;
    WriteTime();
    delay(250);
  //  simulate press of 3 button on IR remote
    pos0=0;pos1=0;colon=1;pos3=1;pos4=3;
    hours=0;minutes=0;seconds=0;
    WriteTime();
    delay(250);
  //  simulate press of 0 button on IR remote
    pos0=0;pos1=1;colon=1;pos3=3;pos4=0;
    hours=0;minutes=0;seconds=0;
    WriteTime();
    delay(250);
  //  simulate press of # button on IR remote
    pos0=0;pos1=1;colon=1;pos3=3;pos4=0;
    hours=1;minutes=30;seconds=0;
    WriteTime();
    delay(5000);
  //1 minute ticks off the clock
    pos0=0;pos1=1;colon=1;pos3=2;pos4=9;
    hours=1;minutes=29;seconds=0;
    WriteTime();
    delay(5000);
  //1 minute ticks off the clock
    pos0=0;pos1=1;colon=1;pos3=2;pos4=8;
    hours=1;minutes=28;seconds=0;
    WriteTime();
    delay(5000);
  //1 minute ticks off the clock
    pos0=0;pos1=1;colon=1;pos3=2;pos4=7;
    hours=1;minutes=27;seconds=0;
    WriteTime();
    delay(5000);
  //1 minute ticks off the clock
    pos0=0;pos1=1;colon=1;pos3=2;pos4=6;
    hours=1;minutes=26;seconds=0;
    WriteTime();
    delay(5000);
  //timer ticks to 1
    pos0=0;pos1=0;colon=1;pos3=0;pos4=1;
    hours=1;minutes=1;seconds=0;
    WriteTime();
    delay(5000);
  //timer ticks to 0
    pos0=0;pos1=0;colon=1;pos3=0;pos4=0;
    hours=1;minutes=0;seconds=0;
    WriteTime();
    delay(5000);
    WriteOFF();
    delay(5000);
// while (hours > 0 || minutes > 0 || seconds >= 0) {
 
// lcd.setCursor(4, 2);
 
// (hours < 10) ? lcd.print("0") : NULL;
// lcd.print(hours);
// lcd.print(":");
// (minutes < 10) ? lcd.print("0") : NULL;
// lcd.print(minutes);
// lcd.print(":");
// (seconds < 10) ? lcd.print("0") : NULL;
// lcd.print(seconds);
// lcd.display();
// stepDown();
// delay(1000);
// }
}
 
void stepDown() {
 if (seconds > 0) {
 seconds -= 1;
 } else {
 if (minutes > 0) {
 seconds = 59;
 minutes -= 1;
 } else {
 if (hours > 0) {
 seconds = 59;
 minutes = 59;
 hours -= 1;
 }
 }
 }

}
void WriteDASH()  {   //  Draw dashes across the display and turn on the : (colon)
  matrix.setBrightness(5);
  matrix.writeDigitRaw(0,0x40);  // Hex map for a hyphen
  matrix.writeDigitRaw(1,0x40); // Hex map for a hyphen
  matrix.drawColon(true);  //  Turn on the colon
  matrix.writeDigitNum(3,0x40);   // Hex map for a hyphen
  matrix.writeDigitRaw(4,0x40);  // Hex map for a hyphen
  matrix.writeDisplay();
}



