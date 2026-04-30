/* ================== PIN DEFINITIONS ================== */
#define LIGHT_RELAY 26   // Active LOW

void setup() {
  pinMode(LIGHT_RELAY, OUTPUT);
}

void loop() {
  digitalWrite(LIGHT_RELAY, LOW);  // ON
  delay(2000);
  digitalWrite(LIGHT_RELAY, HIGH); // OFF
  delay(2000);
}
