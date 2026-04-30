/* ================== PIN DEFINITIONS ================== */
#define PIR_PIN 2

void setup() {
  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    Serial.println("Motion Detected");
  } else {
    Serial.println("No Motion");
  }
  delay(1000);
}
