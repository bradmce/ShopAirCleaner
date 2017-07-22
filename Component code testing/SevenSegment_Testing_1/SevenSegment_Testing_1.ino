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

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();


void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
  matrix.setBrightness(5);
}

void loop() {
  
  // print with print/println
//  for (uint16_t counter = 0; counter < 9999; counter++) {
//    matrix.println(counter);
//    matrix.writeDisplay();
//    delay(10);
//  }

    matrix.print(1234);
    matrix.drawColon(true);
    matrix.writeDisplay();
    delay(1000);
    WriteLO();
    delay(1000);
    WriteHI();
    delay(1000);
    WriteOFF();
    delay(1000);
    WriteBLANK();
    delay(1000);
}

void WriteLO()  {   //  Only draw "_LO_" to the 7-segment display, no mode or relay changes included here
    matrix.writeDigitRaw(0,0x0);  //blank pixel
    matrix.writeDigitRaw(1,0x38); // Hex map for letter L
    matrix.drawColon(false);  //  Turn off the colon
    matrix.writeDigitNum(3, 0);   // zero
    matrix.writeDigitRaw(4,0x0);  //blank pixel
    matrix.writeDisplay();
}
void WriteHI()  {   //  Only draw "_HI_" to the 7-segment display, no mode or relay changes included here
    matrix.writeDigitRaw(0,0x0);  //blank pixel
    matrix.writeDigitRaw(1,0x76); // Hex map for letter L
    matrix.drawColon(false);  //  Turn off the colon
    matrix.writeDigitNum(3, 1);   // zero
    matrix.writeDigitRaw(4,0x0);  //blank pixel
    matrix.writeDisplay();
}
void WriteOFF()  {   //  Only draw "_OFF" to the 7-segment display, no mode or relay changes included here
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
