/* ================== PIN DEFINITIONS ================== */
#define FAN_RELAY 25   // fan active LOW

void setup() {
  pinMode(FAN_RELAY, OUTPUT);
}

void loop() {
  digitalWrite(FAN_RELAY, LOW);
  delay(3000);
  digitalWrite(FAN_RELAY, HIGH);
  delay(3000);
}
