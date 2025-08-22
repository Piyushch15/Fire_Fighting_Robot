// CODE FOR ARDUINO
#include <Servo.h>

// Flame sensor pins
#define FLAME_SENSOR_LEFT A1
#define FLAME_SENSOR_CENTER A2
#define FLAME_SENSOR_RIGHT A3

// Motor driver pins
#define MOTOR_L1 5
#define MOTOR_L2 6
#define MOTOR_R1 9
#define MOTOR_R2 10

// Relay and Servo pins
#define RELAY_PIN 7
#define SERVO_PIN 3

// Optional: Debug LED
#define FIRE_LED 13

// Adjust based on testing (Lower = More Fire)
#define FIRE_THRESHOLD 400

Servo waterServo;

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_L2, OUTPUT);
  pinMode(MOTOR_R1, OUTPUT);
  pinMode(MOTOR_R2, OUTPUT);

  // Relay pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Pump OFF

  // Servo
  waterServo.attach(SERVO_PIN);
  waterServo.write(90);  // Center position

  // Flame sensor pins
  pinMode(FLAME_SENSOR_LEFT, INPUT);
  pinMode(FLAME_SENSOR_CENTER, INPUT);
  pinMode(FLAME_SENSOR_RIGHT, INPUT);

  // Optional: Debug LED
  pinMode(FIRE_LED, OUTPUT);
  digitalWrite(FIRE_LED, LOW);

  Serial.println("🤖 Robot Ready...");
}

void loop() {
  int flameLeft = analogRead(FLAME_SENSOR_LEFT);
  int flameCenter = analogRead(FLAME_SENSOR_CENTER);
  int flameRight = analogRead(FLAME_SENSOR_RIGHT);

  Serial.print("Left: "); Serial.print(flameLeft);
  Serial.print(" | Center: "); Serial.print(flameCenter);
  Serial.print(" | Right: "); Serial.println(flameRight);

  bool fireLeft = flameLeft < FIRE_THRESHOLD;
  bool fireCenter = flameCenter < FIRE_THRESHOLD;
  bool fireRight = flameRight < FIRE_THRESHOLD;

  // Optional LED Indicator
  digitalWrite(FIRE_LED, fireLeft || fireCenter || fireRight ? HIGH : LOW);

  if (fireCenter) {
    Serial.println("🔥 Fire Ahead. Approaching...");
    moveForward();
    delay(300);
    stopMotors();

    // Re-check to avoid false fire
    flameCenter = analogRead(FLAME_SENSOR_CENTER);
    if (flameCenter < FIRE_THRESHOLD) {
      Serial.println("🛑 Close to fire. Stopping and spraying...");
      stopMotors();
      activateWaterPump();
    }
  }
  else if (fireLeft) {
    Serial.println("↩ Fire on Left. Turning...");
    turnLeft();
    delay(300);
    stopMotors();
  }
  else if (fireRight) {
    Serial.println("↪ Fire on Right. Turning...");
    turnRight();
    delay(300);
    stopMotors();
  }
  else {
    Serial.println("✅ No Fire. Standing by...");
    stopMotors();
    deactivateWaterPump();
  }

  delay(500);  // Wait to stabilize sensor readings
}

// === MOTOR CONTROL ===
void moveForward() {
  digitalWrite(MOTOR_L1, HIGH);
  digitalWrite(MOTOR_L2, LOW);
  digitalWrite(MOTOR_R1, HIGH);
  digitalWrite(MOTOR_R2, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR_L1, LOW);
  digitalWrite(MOTOR_L2, HIGH);
  digitalWrite(MOTOR_R1, HIGH);
  digitalWrite(MOTOR_R2, LOW);
}

void turnRight() {
  digitalWrite(MOTOR_L1, HIGH);
  digitalWrite(MOTOR_L2, LOW);
  digitalWrite(MOTOR_R1, LOW);
  digitalWrite(MOTOR_R2, HIGH);
}

void stopMotors() {
  digitalWrite(MOTOR_L1, LOW);
  digitalWrite(MOTOR_L2, LOW);
  digitalWrite(MOTOR_R1, LOW);
  digitalWrite(MOTOR_R2, LOW);
}

// === WATER PUMP & SERVO ===
void activateWaterPump() {
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("🚿 Spraying Water...");

  for (int pos = 60; pos <= 120; pos += 5) {
    waterServo.write(pos);
    delay(50);
  }

  for (int pos = 120; pos >= 60; pos -= 5) {
    waterServo.write(pos);
    delay(50);
  }

  delay(500);
  deactivateWaterPump();
}

void deactivateWaterPump() {
  digitalWrite(RELAY_PIN, LOW);
  waterServo.write(90);  // Reset servo to center
  Serial.println("🛑 Pump Off.");
}
