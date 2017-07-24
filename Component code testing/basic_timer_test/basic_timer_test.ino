
int pos0 = 0;
int pos1 = 1;
int pos2 = 2;
int pos3 = 7;
int minutes =0;
int mode = 0;
String strminutes;
int timerrunning = 0;
int loopcount = 0;
int seconds = 0;

void setup() {
  Serial.begin(9600);
  strminutes = pos0;
  strminutes += pos1;
  strminutes += pos2;
  strminutes += pos3;
  minutes = strminutes.toInt();
  timerrunning = 1;
  Serial.print("Starting minutes: ");
  Serial.println(minutes);

}

void loop() {
  //if IR input ... {

  //} end IR if block

  if (timerrunning==1)  { //means the timer is set and active
    loopcount++;
    delay(100);
    if (loopcount==10) {
      seconds++;
      loopcount = 0;
    }
    if (seconds==60) {
      minutes--;
      seconds = 0;
      Serial.print("Minutes remaining: ");
      Serial.println(minutes);
    }
  }
}

