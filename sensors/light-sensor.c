 /* ================== PIN DEFINITIONS ================== */
 #define LDR_PIN 36

void setup() {
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
}

void loop() {
  int ldr = analogRead(LDR_PIN);
  Serial.println(ldr);
  delay(1000);
}
