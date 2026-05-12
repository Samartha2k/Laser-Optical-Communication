String message;
int laserPin = 9;
void setup() {
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
  Serial.println("Enter your message: ");
}
void loop() {
  if (Serial.available() > 0) {
    message = Serial.readStringUntil('\n');
    transmitMessage(message);
  }
}
void transmitMessage(String msg) {
  for (int i = 0; i < msg.length(); i++) {
    char character = msg[i];
    int position = getPosition(character);
    if (position > 0) {
      int delayTime = position * 4;
      digitalWrite(laserPin, HIGH);
      delay(delayTime);
      digitalWrite(laserPin, LOW);
      delay(100);
    }
  }
}
int getPosition(char character) {
  if (isAlpha(character)) {
    return toupper(character) - 'A' + 1;
  }
  if (character >= '0' && character <= '9') {
    return character - '0' + 27;
  }
  switch (character) {
    case ' ': return 37;
    case '.': return 38;
    case '-': return 39;
    case '=': return 40;
    case '+': return 41;
    case '>': return 42;
    case '<': return 43;
    case '/': return 44;
    case '?': return 45;
    case '*': return 46;
    case '&': return 47;
    case '^': return 48;
    case '%': return 49;
    case '$': return 50;
    case '#': return 51;
    case '@': return 52;
    case '!': return 53;
    default: return -1;
  }
}
