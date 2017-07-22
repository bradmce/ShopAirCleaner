
int LoRelay = 9;
int HiRelay = 8;

void setup() {
  pinMode(LoRelay, OUTPUT);
  pinMode(HiRelay, OUTPUT);
}

void loop() {
  FanLow();
  delay(2000);
  FanHi();
  delay(2000);
  FanOff();
  delay(2000);
}
void FanLow() {
  digitalWrite(HiRelay, LOW);
  delay(500);
  digitalWrite(LoRelay, HIGH);
}
void FanHi()  {
  digitalWrite(LoRelay, LOW);
  delay(500);
  digitalWrite(HiRelay, HIGH);
}
void FanOff()  {
  digitalWrite(LoRelay, LOW);
  digitalWrite(HiRelay, LOW);
}
