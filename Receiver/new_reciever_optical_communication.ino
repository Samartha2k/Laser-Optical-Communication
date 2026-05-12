#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ldrPin = A1; 
const int threshold = 200;
const int irSensorPin = 2;
String decodedMessage = "";

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Receiving...");
  lcd.setCursor(0, 1);
  pinMode(irSensorPin, INPUT);
}

void loop() {
  if (digitalRead(irSensorPin) == LOW) {
    lcd.clear();
    decodedMessage = "";
    Serial.println("LCD Cleared by IR Sensor");
  }
  
  if (detectLaserPulse()) {
    int pulseDuration = measurePulseDuration();
    char decodedChar = decodeCharacter(pulseDuration);
    
    if (decodedChar != '\0') {
      decodedMessage += decodedChar;
      lcd.clear();
      
      int messageLength = decodedMessage.length();
      if (messageLength <= 16) {
        lcd.setCursor(0, 0);
        lcd.print(decodedMessage);
      } else if (messageLength <= 32) {
        lcd.setCursor(0, 0);
        lcd.print(decodedMessage.substring(0, 16));
        lcd.setCursor(0, 1);
        lcd.print(decodedMessage.substring(16));
      } else {
        lcd.setCursor(0, 0);
        lcd.print(decodedMessage.substring(messageLength - 32, messageLength - 16));
        lcd.setCursor(0, 1);
        lcd.print(decodedMessage.substring(messageLength - 16));
      }
      
      Serial.print(decodedChar);
    }
  }
}

bool detectLaserPulse() {
  int ldrValue = analogRead(ldrPin);
  return ldrValue > threshold;
}

int measurePulseDuration() {
  unsigned long startTime = millis();
  while (analogRead(ldrPin) > threshold) {
  }
  unsigned long duration = millis() - startTime;
  int roundedDuration = ((duration + 2) / 4) * 4;
  return roundedDuration;
}

char decodeCharacter(int duration) {
  int position = duration / 4;
  if (position >= 1 && position <= 53) {
    return mapPositionToChar(position);
  } else {
    return '\0';
  }
}

char mapPositionToChar(int position) {
  if (position >= 1 && position <= 26) {
    return 'A' + position - 1;
  }
  if (position >= 27 && position <= 36) {
    return '0' + position - 27;
  }
  switch (position) {
    case 37: return ' ';
    case 38: return '.';
    case 39: return '-';
    case 40: return '=';
    case 41: return '+';
    case 42: return '>';
    case 43: return '<';
    case 44: return '/';
    case 45: return '?';
    case 46: return '*';
    case 47: return '&';
    case 48: return '^';
    case 49: return '%';
    case 50: return '$';
    case 51: return '#';
    case 52: return '@';
    case 53: return '!';
    default: return '\0';
  }
}
