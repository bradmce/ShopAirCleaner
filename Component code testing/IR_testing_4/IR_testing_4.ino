/* YourDuino.com Example Software Sketch
 IR Remote Kit Test: Returns numeric value for button pressed
 Uses YourDuino.com IR Infrared Remote Control Kit V2
 http://arduino-direct.com/sunshop/index.php?l=product_detail&p=153
 based on code by Ken Shirriff - http://arcfn.com
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include "IRremote.h"
#include "IRremoteInt.h"

/*-----( Declare Constants )-----*/
#define  REPEAT_DELAY  500   // Delay before checking for another button / repeat
int receiver = 11; // pin 1 of IR receiver to Arduino digital pin 11
                   // NOTE: Other pins can be used, except pin 3 and 13
                  
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'

/*-----( Declare Variables )-----*/
int  ButtonValue;  // 0..9,100,200, top 9 buttons encoded 10..18, -1 Bad Code


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
//    Serial.println(results.value, HEX); // UN Comment to see raw values
    ButtonValue = translateIR(); 
    Serial.println(ButtonValue, DEC);
    delay(REPEAT_DELAY);    // Adjust for repeat / lockout time
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Declare User-written Functions )-----*/
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


