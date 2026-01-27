#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

// -----------------------
// Pin Definitions
// -----------------------
#define RELAY_PIN 7        // Relay to control ignition
#define BUTTON_PIN 2       // Optional start button

// -----------------------
// LCD Setup
// -----------------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -----------------------
// MQ3 Alcohol Sensor Pin
// -----------------------
#define MQ3_PIN A0
#define ALCOHOL_THRESHOLD 200  // Adjust based on calibration

// -----------------------
// Fingerprint Sensor Setup
// -----------------------
SoftwareSerial mySerial(10, 11); // RX, TX pins for R307
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// -----------------------
// Setup
// -----------------------
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, LOW); // Ensure ignition is OFF

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Starter");

  Serial.begin(9600);
  while (!Serial); // Wait for serial monitor

  // Initialize fingerprint sensor
  if (finger.begin(57600)) {
    Serial.println("Fingerprint sensor detected!");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Ready");
  } else {
    Serial.println("Fingerprint sensor not found");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error");
    while (1); // Halt
  }
}

// -----------------------
// Main Loop
// -----------------------
void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place Finger");

  int alcoholValue = analogRead(MQ3_PIN);
  Serial.print("Alcohol Sensor: ");
  Serial.println(alcoholValue);

  // Check for alcohol first
  if (alcoholValue > ALCOHOL_THRESHOLD) {
    lcd.setCursor(0, 1);
    lcd.print("Alcohol Detected");
    digitalWrite(RELAY_PIN, LOW); // Prevent ignition
    delay(3000);
    return;
  }

  // Read fingerprint
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return;

  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.print("Authorized ID: "); Serial.println(finger.fingerID);
    lcd.setCursor(0, 1);
    lcd.print("Authorized! Start");
    digitalWrite(RELAY_PIN, HIGH); // Turn on ignition
    delay(5000); // Keep ignition ON for demonstration
    digitalWrite(RELAY_PIN, LOW);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Access Denied");
    Serial.println("Fingerprint not recognized");
    digitalWrite(RELAY_PIN, LOW);
    delay(2000);
  }
}

