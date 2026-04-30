/* ================== PIN DEFINITIONS ================== */

#include <WiFi.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

/* ================== WiFi ================== */
#define WIFI_SSID       "UN"
#define WIFI_PASSWORD   "234567MIU"

/* ================== SENSOR PINS ================== */
#define PIR_PIN         19
#define MQ2_AO          34
#define MQ2_DO          16
#define TRIG_PIN        32
#define ECHO_PIN        33
#define LDR_PIN         36
#define DOOR_PIN        4
#define FLAME_PIN       27
#define SOUND_PIN       14

/* ================== OUTPUT PINS ================== */
#define LIGHT_RELAY     26
#define FAN_RELAY       25
#define LED_PIN         5
#define BUZZER_PIN      13

/* ================== LCD ================== */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ================== RFID ================== */
#define RFID_SS   15
#define RFID_RST  2
MFRC522 rfid(RFID_SS, RFID_RST);

/* ================== KEYPAD ================== */
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {18, 23, 17, 16};
byte colPins[COLS] = {12, 14, 27, 33};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* ================== ACCESS ================== */
String correctPassword = "1234";
String enteredPassword = "";
String allowedUID = "A3 B2 C1 D4";

/* ================== SETUP ================== */
void setup() {
  Serial.begin(115200);

  pinMode(LIGHT_RELAY, OUTPUT);
  pinMode(FAN_RELAY, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(PIR_PIN, INPUT);
  pinMode(MQ2_DO, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(FLAME_PIN, INPUT);
  pinMode(SOUND_PIN, INPUT);

  digitalWrite(LIGHT_RELAY, HIGH);
  digitalWrite(FAN_RELAY, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  analogSetAttenuation(ADC_11db);

  lcd.init();
  lcd.backlight();
  lcd.print("Scan Card or");
  lcd.setCursor(0,1);
  lcd.print("Enter Password");

  SPI.begin();
  rfid.PCD_Init();

  /* ===== WiFi Connect ===== */
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lcd.clear();
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);
  resetLCD();
}

/* ================== LOOP ================== */
void loop() {

  int pir = digitalRead(PIR_PIN);
  int gasDigital = digitalRead(MQ2_DO);
  int flame = digitalRead(FLAME_PIN);
  int ldr = analogRead(LDR_PIN);

  digitalWrite(LED_PIN, pir ? HIGH : LOW);

  /* ===== Buzzer ONLY Gas + Flame ===== */
  if (gasDigital == LOW || flame == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  /* ===== RFID ===== */
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) uid += " ";
    }
    uid.toUpperCase();

    lcd.clear();
    lcd.print(uid == allowedUID ? "Access Granted" : "Access Denied");
    delay(2000);
    resetLCD();
    rfid.PICC_HaltA();
  }

  /* ===== KEYPAD ===== */
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      lcd.clear();
      lcd.print(enteredPassword == correctPassword ? "Access Granted" : "Wrong Password");
      enteredPassword = "";
      delay(2000);
      resetLCD();
    } 
    else if (key == '*') {
      enteredPassword = "";
    } 
    else {
      enteredPassword += key;
      lcd.setCursor(0,1);
      lcd.print(enteredPassword);
    }
  }
}

/* ================== RESET LCD ================== */
void resetLCD() {
  lcd.clear();
  lcd.print("Scan Card or");
  lcd.setCursor(0,1);
  lcd.print("Enter Password");
}
