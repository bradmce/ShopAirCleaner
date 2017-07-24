
int pos0,pos1,pos2,pos3;
int minutes = 1875;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting minutes: ");
  Serial.println(minutes);

}

void loop() {
  if (minutes < 10)  {  //  single digit value
    pos0 = 0;
    pos1 = 0;
    pos2 = 0;
    pos3 = minutes;
  } else if (minutes < 100) { // double digit value
    pos0 = 0;
    pos1 = 0;
    pos2 = minutes / 10;
    pos3 = minutes - (pos2 * 10);
  } else if (minutes < 1000) {  //  three digit value
    pos0 = 0;
    pos1 = minutes / 100;
    pos2 = (minutes - (pos1 * 100)) / 10;
    pos3 = minutes - (pos1 * 100) - (pos2 * 10);
  } else if (minutes > 999) {  //  four digit value    
    pos0 = minutes / 1000;
    pos1 = (minutes - (pos0 * 1000)) / 100;
    pos2 = (minutes - (pos0 * 1000) - (pos1 * 100)) / 10;
    pos3 = minutes - (pos0 * 1000) - (pos1 * 100) - (pos2 * 10);
  }
  Serial.print("Current minutes value: ");
  Serial.println(minutes);
  Serial.print("Value of pos0 is: ");Serial.println(pos0);
  Serial.print("Value of pos1 is: ");Serial.println(pos1);
  Serial.print("Value of pos2 is: ");Serial.println(pos2);
  Serial.print("Value of pos3 is: ");Serial.println(pos3);
  minutes--;
  delay(3000);
}

