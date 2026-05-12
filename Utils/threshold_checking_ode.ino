const int ldrPin = A1;

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
}

void loop() {
  int lightLevel = analogRead(ldrPin);   // Read the analog value from LDR
  Serial.println(lightLevel);            // Print the value to Serial Monitor
  delay(4);                            // Small delay for readability
}
