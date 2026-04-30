#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* ================== BLUETOOTH ================== */
SoftwareSerial BT(2, 3); // RX, TX

/* ================== LCD ================== */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ================== KEYPAD ================== */
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* ================== SENSORS ================== */
#define PIR_PIN     12
#define MQ2_DO      A0
#define FLAME_PIN   A1
#define LDR_PIN     A2
#define TRIG_PIN    A3
#define ECHO_PIN    A4   // استخدمنا A4 رقمي
/* ================== OUTPUTS ================== */
#define LIGHT_RELAY  A5   // Active LOW
#define FAN_RELAY    13   // Active LOW
#define BUZZER_PIN   3    // لو مش مستخدم BT TX

/* ================== ACCESS ================== */
String correctPassword = "1234";
String enteredPassword = "";

/* ================== SETUP ================== */
void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(PIR_PIN, INPUT);
  pinMode(MQ2_DO, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LIGHT_RELAY, OUTPUT);
  pinMode(FAN_RELAY, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LIGHT_RELAY, HIGH);
  digitalWrite(FAN_RELAY, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.print("Enter Password");
}

/* ================== LOOP ================== */
void loop() {

  /* ===== SENSORS ===== */
  int pir = digitalRead(PIR_PIN);
  int gas = digitalRead(MQ2_DO);
  int flame = digitalRead(FLAME_PIN);
  int ldr = analogRead(LDR_PIN);

  /* ===== ULTRASONIC ===== */
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = duration / 58;

  /* ===== SAFETY ===== */
  if (gas == LOW || flame == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  /* ===== KEYPAD ===== */
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      lcd.clear();
      if (enteredPassword == correctPassword) {
        lcd.print("Access Granted");
        digitalWrite(LIGHT_RELAY, LOW);
      } else {
        lcd.print("Wrong Password");
      }
      enteredPassword = "";
      delay(2000);
      lcd.clear();
      lcd.print("Enter Password");
    }
    else if (key == '*') {
      enteredPassword = "";
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
    else {
      enteredPassword += key;
      lcd.setCursor(0,1);
      lcd.print(enteredPassword);
    }
  }

  /* ===== BLUETOOTH ===== */
  if (BT.available()) {
    char cmd = BT.read();
    if (cmd == 'L') digitalWrite(LIGHT_RELAY, LOW);
    if (cmd == 'l') digitalWrite(LIGHT_RELAY, HIGH);
    if (cmd == 'F') digitalWrite(FAN_RELAY, LOW);
    if (cmd == 'f') digitalWrite(FAN_RELAY, HIGH);
  }

  /* ===== DEBUG ===== */
  Serial.print("PIR: "); Serial.print(pir);
  Serial.print(" | Gas: "); Serial.print(gas);
  Serial.print(" | Flame: "); Serial.print(flame);
  Serial.print(" | LDR: "); Serial.print(ldr);
  Serial.print(" | Distance: "); Serial.println(distance);

  delay(300);
}
