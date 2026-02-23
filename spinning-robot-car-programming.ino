// Motor driver pins
const int IN1 = 7;   // Right side
const int IN2 = 8;
const int IN3 = 9;   // Left side
const int IN4 = 10;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {

  // -------- FORWARD (5 seconds) --------
  digitalWrite(IN1, HIGH);  // Right forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);  // Left forward
  digitalWrite(IN4, LOW);
  delay(5000);

  // -------- TURN RIGHT (1 second) --------
  // Left side forward, right side backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(1000);

  // -------- TURN RIGHT AGAIN (1 second) --------
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(1000);

  // -------- STOP --------
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  while(true); // stop forever
}
