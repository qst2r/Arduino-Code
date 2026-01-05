/*
  Smart Trash Can – Enhanced Version (Based on Original Code)

  NEW FEATURES:
  - LED status indicators
  - Anti-spam delay
  - Ultrasonic timeout safety
  - Fixed if-statement logic
*/

#include <Servo.h>

// ================= SERVO =================
Servo servo;
const int servoPin = 9;
const int openAngle = 0;
const int closeAngle = 90;

// ================= ULTRASONIC =================
const int trigPin = 5;
const int echoPin = 6;
long distance, averageDistance;
long averDist[3];

// ================= THRESHOLD =================
const int distanceThreshold = 20;

// ================= NEW: LED PINS =================
const int redLED = 10;    // Lid open
const int greenLED = 11; // Lid closed

// ================= NEW: ANTI-SPAM TIMER =================
unsigned long lastActionTime = 0;
const unsigned long cooldownTime = 4000; // ms

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // NEW: LED setup
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, HIGH);

  servo.attach(servoPin);
  servo.write(closeAngle);
  delay(200);
  servo.detach();
}

void loop() {

  // Read distance 3 times (same logic as original)
  for (int i = 0; i <= 2; i++) {
    distance = readDistance();
    averDist[i] = distance;
    delay(10);
  }

  // Average distance
  averageDistance = (averDist[0] + averDist[1] + averDist[2]) / 3;
  Serial.println(averageDistance);

  // NEW: cooldown check
  if (millis() - lastActionTime < cooldownTime) return;

  // ================= FIXED IF LOGIC =================
  if (averageDistance <= distanceThreshold) {

    servo.attach(servoPin);
    delay(1);
    servo.write(openAngle);

    // NEW: LED feedback
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    delay(3000);

    servo.write(closeAngle);
    delay(800);
    servo.detach();

    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);

    lastActionTime = millis();
  }
}

// ================= FUNCTION =================
float readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // NEW: timeout added
  long duration = pulseIn(echoPin, HIGH, 25000);
  if (duration == 0) return 999;

  return duration / 58.0;
}
