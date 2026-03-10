/*
 * Dual Sensor LED Control - Arduino Nano
 * =======================================
 * 
 * 1. IR Sensor: 
 *    - Input: D2
 *    - Output: LED at D8 (lights up for 3 seconds when detected)
 * 
 * 2. Ultrasonic Sensor (HC-SR04):
 *    - TRIG: D6, ECHO: D4
 *    - Range 0-15cm:  LED at D9 lights up
 *    - Range 7-23cm:  LED at D11 lights up
 *    - Range 15-30cm: LED at D12 lights up
 */

// ===== PIN DEFINITIONS =====
const int IR_SENSOR_PIN = 2;
const int LED_IR_PIN    = 7;

const int TRIG_PIN      = 6; // Updated to pin 6
const int ECHO_PIN      = 4;
const int LED_RANGE1_PIN = 9;   // 0-15cm
const int LED_RANGE2_PIN = 11;  // 7-23cm
const int LED_RANGE3_PIN = 12;  // 15-30cm

// ===== CONSTANTS =====
const unsigned long IR_TIMER_DURATION = 3000; // 3 seconds

// ===== GLOBALS =====
unsigned long irLedOnTime = 0; // Stores the timestamp of last IR detection

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  
  // IR Sensor pins
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_IR_PIN,    OUTPUT);

  // Ultrasonic Sensor pins
  pinMode(TRIG_PIN,      OUTPUT);
  pinMode(ECHO_PIN,      INPUT);
  pinMode(LED_RANGE1_PIN, OUTPUT);
  pinMode(LED_RANGE2_PIN, OUTPUT);
  pinMode(LED_RANGE3_PIN, OUTPUT);

  Serial.println(F("System Initialized"));
  Serial.println(F("Monitoring IR and Ultrasonic sensors..."));
}

// ===== MAIN LOOP =====
void loop() {
  handleIRSensor();
  handleUltrasonicSensor();
  checkIRTimer();
  
  delay(50); // Reduced delay for more responsive detection
}

// ===== IR SENSOR HANDLER =====
void handleIRSensor() {
  // Most IR proximity sensors (like HW-201) output LOW when an object is detected
  int irValue = digitalRead(IR_SENSOR_PIN);
  
  if (irValue == LOW) {
    digitalWrite(LED_IR_PIN, HIGH);
    irLedOnTime = millis(); // Refresh/Set the timer
  }
}

// ===== CHECK IR TIMER =====
void checkIRTimer() {
  // If the LED is ON and time has passed the duration, turn it OFF
  if (irLedOnTime > 0 && (millis() - irLedOnTime >= IR_TIMER_DURATION)) {
    digitalWrite(LED_IR_PIN, LOW);
    irLedOnTime = 0; // Reset timer
  }
}

// ===== ULTRASONIC SENSOR HANDLER =====
void handleUltrasonicSensor() {
  float distance = measureDistance();
  
  // Serial output for debugging
  if (distance > 0 && distance < 400) {
    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.println(F(" cm"));
  }

  // --- Range Logic ---
  
  // Range 1: 0-15 cm -> Pin D9
  if (distance >= 0 && distance <= 13) {
    digitalWrite(LED_RANGE1_PIN, HIGH);
  } else {
    digitalWrite(LED_RANGE1_PIN, LOW);
  }

  // Range 2: 7-23 cm -> Pin D11
  if (distance >= 7 && distance <= 23) {
    digitalWrite(LED_RANGE2_PIN, HIGH);
  } else {
    digitalWrite(LED_RANGE2_PIN, LOW);
  }

  // Range 3: 15-30 cm -> Pin D12
  if (distance >= 17 && distance <= 30) {
    digitalWrite(LED_RANGE3_PIN, HIGH);
  } else {
    digitalWrite(LED_RANGE3_PIN, LOW);
  }
}

// ===== DISTANCE MEASUREMENT FUNCTION =====
float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // pulseIn returns the duration in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  
  if (duration == 0) return 999; // No echo detected

  // Speed of sound is ~0.0343 cm/us. Distance = (time * speed) / 2
  float distance = (duration * 0.0343) / 2.0;
  return distance;
}
