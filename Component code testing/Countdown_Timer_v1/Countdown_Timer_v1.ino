
int controlPin = 13;
char currentTimeValue[4];
int currentState = 1;
int timerSeconds = 0;
int lpcnt = 0;



void setup()
{

 //setup default time to 00:00
 currentTimeValue[0]='0';
 currentTimeValue[1]='0';
 currentTimeValue[2]='0';
 currentTimeValue[3]='0';
 showEnteredTime();
}

void loop()
{
 int l;
 char tempVal[3];
 char key = keypad.getKey();

 //key pressed and state is 1
 if (int(key) != 0 and currentState == 1) {

 switch (key) {
 case '*':
 relayStatus(false);
 currentTimeValue[0]='0';
 currentTimeValue[1]='0';
 currentTimeValue[2]='0';
 currentTimeValue[3]='0';
 showEnteredTime();
 currentState = 1;

 lpcnt = 0;
 timerSeconds = 0;
 break;

 case '#':
 tempVal[0] = currentTimeValue[0];
 tempVal[1] = currentTimeValue[1];
 tempVal[2] = 0;

 timerSeconds = atol(tempVal) * 60;

 tempVal[0] = currentTimeValue[2];
 tempVal[1] = currentTimeValue[3];
 tempVal[2] = 0;

 timerSeconds = timerSeconds + atol(tempVal);
 currentState = 2;
 break;

 default:
 currentTimeValue[0] = currentTimeValue[1];
 currentTimeValue[1] = currentTimeValue[2];
 currentTimeValue[2] = currentTimeValue[3];
 currentTimeValue[3] = key;
 showEnteredTime();
 break;
 }
 }

 if (currentState == 2) {
 if (int(key) != 0) {
 if (key == '*') {
 relayStatus(false);
 displayCodeEntryScreen();
 currentTimeValue[0]='0';
 currentTimeValue[1]='0';
 currentTimeValue[2]='0';
 currentTimeValue[3]='0';
 showEnteredTime();
 currentState = 1;
 lpcnt = 0;
 timerSeconds = 0;
 }
 } else {

 if (lpcnt > 9) {
 lpcnt = 0;
 --timerSeconds;
 showCountdown();

 if (timerSeconds <= 0) {
 currentState = 1;
 relayStatus(false);
 displayCodeEntryScreen();
 showEnteredTime();
 } else {
 relayStatus(true);
 }
 }

 ++lpcnt;
 delay(100);
 }
 }
}

void showEnteredTime()
{
 lcd.setCursor(14,3);
 lcd.print(currentTimeValue[0]);
 lcd.print(currentTimeValue[1]);
 lcd.print(":");
 lcd.print(currentTimeValue[2]);
 lcd.print(currentTimeValue[3]);
}


