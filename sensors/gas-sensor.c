/* ================== PIN DEFINITIONS ================== */
#define MQ2_AO 34
#define MQ2_DO 16

void setup() {
  Serial.begin(115200);
  pinMode(MQ2_DO, INPUT);
}

void loop() {
  int gasA = analogRead(MQ2_AO);
  int gasD = digitalRead(MQ2_DO);

  Serial.print("Analog: ");
  Serial.print(gasA);
  Serial.print(" | Digital: ");
  Serial.println(gasD);

  delay(1000);
}
