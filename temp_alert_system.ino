// Project: Smart Temperature Alert System (Initial v1.0 - Contains QA Bugs)
const int tempPin = A0;     // LM35 Temperature Sensor
const int redLed = 13;      // Overheat Warning LED
const int greenLed = 12;    // Normal Operation LED
const int buzzer = 8;       // Alert Buzzer

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  // BUG 1: Forgot pinMode(greenLed, OUTPUT) and pinMode(buzzer, OUTPUT)
}

void loop() {
  int rawValue = analogRead(tempPin);
  // BUG 2: Wrong ADC reference formula (using 3.3V math on a 5V Arduino Uno)
  float voltage = rawValue * (3.3 / 1024.0); 
  float tempC = voltage * 100.0;

  Serial.print("Temperature: ");
  Serial.println(tempC);

  // BUG 3: No hysteresis (causes rapid LED/buzzer flickering around 30.0°C)
  if (tempC > 30.0) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW);
  }
  
  // BUG 4: Blocking delay(5000) makes system unresponsive to sudden spikes
  delay(5000); 
}
