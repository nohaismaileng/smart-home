/* ================== PIN DEFINITIONS ================== */
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

/* ================= LCD ================= */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ================= RFID ================= */
#define SS_PIN   5
#define RST_PIN  27
MFRC522 rfid(SS_PIN, RST_PIN);

/* ================= KEYPAD ================= */
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {32, 33, 25, 26};
byte colPins[COLS] = {14, 12, 13, 4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* ================= PASSWORD & RFID ================= */
String correctPassword = "1234";
String enteredPassword = "";

// UID بتاع الكارت (غيره بالكارت بتاعك)
String allowedUID = "A3 B2 C1 D4";

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Scan Card or");
  lcd.setCursor(0,1);
  lcd.print("Enter Password");

  SPI.begin();
  rfid.PCD_Init();
}

void loop() {

  /* ===== RFID PART ===== */
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) uid += " ";
    }
    uid.toUpperCase();

    lcd.clear();
    if (uid == allowedUID) {
      lcd.print("Access Granted");
      Serial.println("RFID OK");
    } else {
      lcd.print("Access Denied");
      Serial.println("RFID FAIL");
    }

    delay(2000);
    resetLCD();
    rfid.PICC_HaltA();
  }

  /* ===== KEYPAD PART ===== */
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {
      lcd.clear();
      if (enteredPassword == correctPassword) {
        lcd.print("Access Granted");
        Serial.println("Password OK");
      } else {
        lcd.print("Wrong Password");
        Serial.println("Password FAIL");
      }
      delay(2000);
      enteredPassword = "";
      resetLCD();
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
}

/* ================= RESET LCD ================= */
void resetLCD() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan Card or");
  lcd.setCursor(0,1);
  lcd.print("Enter Password");
}
