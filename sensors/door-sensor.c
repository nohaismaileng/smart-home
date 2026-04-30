/* ================== PIN DEFINITIONS ================== */
#define PIR_PIN 4 

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    Serial.println(1);]
  } else {
    Serial.println(0); 
  }

  delay(1000); 
}
