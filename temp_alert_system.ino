// Project: Smart Temperature Alert System (Fixed v2.0)
const int tempPin = A0;
const int redLed = 13;
const int greenLed = 12;
const int buzzer = 8;

unsigned long previousMillis = 0;
const long interval = 500; // Non-blocking 500ms sampling
bool alertState = false;

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT); // Fixed Issue #1
  pinMode(buzzer, OUTPUT);   // Fixed Issue #1
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) { // Fixed Issue #4
    previousMillis = currentMillis;

    int rawValue = analogRead(tempPin);
    float voltage = rawValue * (5.0 / 1024.0); // Fixed Issue #2
    float tempC = voltage * 100.0;

    Serial.print("Temperature (°C): ");
    Serial.println(tempC);

    // Fixed Issue #3: Added 2°C Hysteresis (Trigger at 30°C, Reset below 28°C)
    if (tempC >= 30.0) {
      alertState = true;
    } else if (tempC <= 28.0) {
      alertState = false;
    }

    digitalWrite(redLed, alertState ? HIGH : LOW);
    digitalWrite(greenLed, alertState ? LOW : HIGH);
    digitalWrite(buzzer, alertState ? HIGH : LOW);
  }
}
