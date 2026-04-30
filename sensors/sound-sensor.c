/* ================== PIN DEFINITIONS ================== */
#define MIC_PIN 32   // Analog pin
#define SAMPLE_TIME 50  

void setup() {
  Serial.begin(9600);

  analogReadResolution(12);              
  analogSetAttenuation(ADC_11db);

void loop() {
  unsigned long startMillis = millis();
  int signalMax = 0;
  int signalMin = 4095;
  //peakToPeak = 700 - 450 = 250


  while (millis() - startMillis < SAMPLE_TIME) {
    int sample = analogRead(MIC_PIN);
    if (sample > signalMax) signalMax = sample;
    if (sample < signalMin) signalMin = sample;
  }

  int peakToPeak = signalMax - signalMin;

  Serial.print("Sound Level: ");
  Serial.println(peakToPeak);

  delay(1000); 
}
