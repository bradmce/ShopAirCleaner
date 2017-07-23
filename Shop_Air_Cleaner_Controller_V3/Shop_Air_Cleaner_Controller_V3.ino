/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED 7-Segment backpacks 
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 /*  based on code by Ken Shirriff - http://arcfn.com
 terry@yourduino.com */

 
#include "IRremote.h"
#include "IRremoteInt.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

//Define state tracking vars
  int mode = 0; //  Off = 0, On = 1, Timer = 2
  int fanspeed = 0; //  Low = 1, Hi = 2
  int timerentry = 0;
  int pos0=0;
  int pos1=0;
  int colon=1;
  int pos2=0;
  int pos3=0;
  int hours = 0; // start hours
  int minutes = 0; //start min
  int seconds = 0; //start seconds
  int timedigits;
  int timelength;

//Define pins for fan speed relays
  int LoRelay = 9;
  int HiRelay = 8;

//IR setup
  #define  REPEAT_DELAY  300   // Delay before checking for another button / repeat
  int receiver = 11; // pin 1 of IR receiver to Arduino digital pin 11
  IRrecv irrecv(receiver);           // create instance of 'irrecv'
  decode_results results;            // create instance of 'decode_results'
  int ButtonValue;
  


void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);  
  pinMode(LoRelay,OUTPUT);
  digitalWrite(LoRelay,HIGH);
  pinMode(HiRelay, OUTPUT);
  digitalWrite(HiRelay,HIGH);

  irrecv.enableIRIn(); // Start the receiver

  matrix.setBrightness(0);  //  dim the brightness while in OFF mode
  WriteOFF();
}

void loop() {
  if (irrecv.decode(&results)) {  // have we received an IR signal?
    ButtonValue = translateIR(); 
    //Serial.println(ButtonValue, DEC);
    switch(ButtonValue)
      {
        case 10:  // Up Arrow pressed - Fan to HI speed
          if (fanspeed!=2) {
            FanHI();
          }
          if (timerentry==1) {
            timerentry = 0;
            timedigits="";
          }
          WriteHI();
          break;
        case 11:  // Down Arrow pressed - Fan to Lo speed
          if (fanspeed!=1) {            
            FanLOW();
          }
          if (timerentry==1) {
            timerentry = 0;
            timedigits="";
          }
          WriteLOW();
          break;
        case 12:  // Left Arrow pressed - Fan Off
          if (fanspeed!=0) {
            WriteOFF();
            FanOFF();
          }
          if (timerentry==1) {
            timerentry = 0;
            timedigits="";
          }
          break;
        case 15:  // *(star) pressed - reset timer entry
          if (timerentry==1) {
            timedigits = 0;
            matrix.writeDigitRaw(0,0x40);  //blank pixel
            matrix.writeDigitRaw(1,0x40);  //blank pixel
            matrix.drawColon(false);  //  Turn off the colon
            matrix.writeDigitRaw(3,0x40);  //blank pixel
            matrix.writeDigitRaw(4,0x40);  //blank pixel
            matrix.writeDisplay();
          }
          break;
        case 16:  // # pressed - Enter Timer Mode
          if (timerentry==0)  { // first time # was pushed, now pay attention to numbers to enter time)
            timerentry = 1;
            timedigits = 0;
            matrix.writeDigitRaw(0,0x40);  //blank pixel
            matrix.writeDigitRaw(1,0x40);  //blank pixel
            matrix.drawColon(false);  //  Turn off the colon
            matrix.writeDigitRaw(3,0x40);  //blank pixel
            matrix.writeDigitRaw(4,0x40);  //blank pixel
            matrix.writeDisplay();
          }
          break;
        case 1:
          if (timerentry==1)  {
            handledigits();
          }
          break;
        case 2:
          if (timerentry==1)  {
            handledigits();
          }
          break;
        case 3:
          if (timerentry==1)  {
            handledigits();
          }
          break;
        case 4:
          if (timerentry==1)  {
            handledigits();
          }
          break;
        case 5:
          if (timerentry==1)  {
            handledigits();
          }
          break;
        case 6:
          if (timerentry==1)  {
            handledigits();
          }
          break;          
        case 7:
          if (timerentry==1)  {
            handledigits();
          }
          break;          
        case 8:
          if (timerentry==1)  {
            handledigits();
          }
          break;
        case 9:
          if (timerentry==1)  {
            handledigits();
          }
          break;
        case 0:
          if (timerentry==1)  {
            handledigits();
          }
          break;
      }
    delay(REPEAT_DELAY);    // Adjust for repeat / lockout time
    irrecv.resume(); // receive the next value
  }
} //end main loop
void handledigits() {
  if (timedigits==0) {
    pos0=0;pos1=0;pos2=0;pos3=ButtonValue;
    timedigits++;
    WriteTime();
  } else if (timedigits==1) {
    pos0=0;pos1=0;pos2=pos3;pos3=ButtonValue;
    timedigits++;
    WriteTime();
  } else if (timedigits==2) {
    pos0=0;pos1=pos2;pos2=pos3;pos3=ButtonValue;
    timedigits++;
    WriteTime();
  } else if (timedigits==3) {
    pos0=pos1;pos1=pos2;pos2=pos3;pos3=ButtonValue;
    timedigits++;
    WriteTime();
  } else if (timedigits==4) {
    pos0=0;pos1=0;pos2=0;pos3=0;
    timedigits=0;
    WriteTime();
  }
}
void WriteLOW()  {   //  Only draw "_LO_" to the 7-segment display, no mode or relay changes included here
  matrix.setBrightness(5);
  matrix.writeDigitRaw(0,0x0);  //blank pixel
  matrix.writeDigitRaw(1,0x38); // Hex map for letter L
  matrix.drawColon(false);  //  Turn off the colon
  matrix.writeDigitNum(3, 0);   // zero
  matrix.writeDigitRaw(4,0x0);  //blank pixel
  matrix.writeDisplay();
}
void WriteHI()  {   //  Only draw "_HI_" to the 7-segment display, no mode or relay changes included here
  matrix.setBrightness(5);
  matrix.writeDigitRaw(0,0x0);  //blank pixel
  matrix.writeDigitRaw(1,0x76); // Hex map for letter L
  matrix.drawColon(false);  //  Turn off the colon
  matrix.writeDigitNum(3, 1);   // zero
  matrix.writeDigitRaw(4,0x0);  //blank pixel
  matrix.writeDisplay();
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
void WriteBLANK()  {   // Blank the display
  matrix.writeDigitRaw(0,0x0);  //blank pixel
  matrix.writeDigitRaw(1,0x0);  //blank pixel
  matrix.drawColon(false);  //  Turn off the colon
  matrix.writeDigitRaw(3,0x0);  //blank pixel
  matrix.writeDigitRaw(4,0x0);  //blank pixel
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
  matrix.writeDigitNum(3,pos2);
  matrix.writeDigitNum(4,pos3);    
  matrix.writeDisplay();
}
void FanLOW() {  
  digitalWrite(HiRelay, HIGH);
  delay(500);
  digitalWrite(LoRelay, LOW);
  fanspeed = 1;
}
void FanHI()  {
  digitalWrite(LoRelay, HIGH);
  delay(500);
  digitalWrite(HiRelay, LOW);
  fanspeed = 2;
}
void FanOFF()  {
  digitalWrite(LoRelay, HIGH);
  digitalWrite(HiRelay, HIGH);
  mode = 0;
  fanspeed = 0;
}
void Expire() {   //function for timer expiration - open relays, reset timer value to 00:00, and set display to off
  FanOFF();
  delay(500);
  WriteOFF();
  delay(500);
  WriteBLANK();
  delay(200);
}
int translateIR() // returns value of "Car MP3 remote IR code received
{
 switch(results.value)
  {
  case 0xFF629D:  return 10;  break;   // UP
  case 0xFFA857:  return 11;  break;   // Down
  case 0xFF22DD:  return 12;  break;   // Left
  case 0xFFC23D:  return 13;  break;   // Right
  case 0xFF02FD:  return 14;  break;   // OK
  case 0xFF6897:  return 1;   break;   // 1 button
  case 0xFF9867:  return 2;   break;   // 2 button
  case 0xFFB04F:  return 3;   break;   // 3 button 
  case 0xFF30CF:  return 4;   break;   // 4 button
  case 0xFF18E7:  return 5;   break;   // 5 button
  case 0xFF7A85:  return 6;   break;   // 6 button
  case 0xFF10EF:  return 7;   break;   // 7 button
  case 0xFF38C7:  return 8;   break;   // 8 button
  case 0xFF5AA5:  return 9;   break;   // 9 button
  case 0xFF4AB5:  return 0;   break;   // 0 button
  case 0xFF42BD:  return 15;  break;   // * button
  case 0xFF52AD:  return 16;  break;   // # button
  case 0xFFFFFFFF:  
    return -2;
    break; // REPEAT: Button Held down longer than 
  default: 
    return -1; // Other Button  / Bad Code
  } //END case
} //END translateIR

