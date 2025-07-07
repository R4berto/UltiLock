#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Password.h>

#define buzzer 13
#define trigPin 12
#define echoPin 11
#define lockDistance 10 // Distance in cm to trigger the lock

Servo servo1; // First servo for the main door
Servo servo2; // Second servo for an additional mechanism (e.g., alarm, light)

LiquidCrystal_I2C lcd(0x27, 16, 2);

String newPasswordString; // Hold the new password
char newPassword[6]; // Character string of newPasswordString
byte a = 5;

bool doorLocked = false;       // Tracks the door's lock state
bool ultrasonicEnabled = true; // Controls ultrasonic sensor activity

Password password = Password("1234"); // Enter your password

byte maxPasswordLength = 6;
byte currentPasswordLength = 0;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'},
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo1.attach(A0); // Corrected pin for servo
  servo1.write(50);  // Initialize to open position
  servo2.attach(A1); // Corrected pin for servo
  servo2.write(50);  // Initialize to open position

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("DOOR LOCK SYSTEM");
  delay(3000);
  lcd.clear();
}

void loop() {
  if (ultrasonicEnabled && checkUltrasonicSensor()) {
    intruderAlert();
  }

  if(doorLocked){
    lcd.setCursor(1, 0);
    lcd.print("ENTER PASSWORD");

    char key = keypad.getKey();
    if (key != NO_KEY) {
      delay(60);
      if (key == 'C') {
        resetPassword();
      } else if (key == 'D') {
        // Manual toggle for testing purposes
        if (doorLocked) {
          unlockDoor();
        } else {
          lockDoor();
        }
      } else {
        processNumberKey(key);
      }
    }
  } else {
    lcd.setCursor(1, 0);
    lcd.print("D to locked");
    lcd.setCursor(0,1);
    lcd.print("Door is unlocked");

    char key = keypad.getKey();
    if (key != NO_KEY) {
      delay(60);
      if (key == 'D') {
        // Manual toggle for testing purposes
        if (doorLocked) {
          unlockDoor();
        } else {
          lockDoor();
        }
      } else {
        processNumberKey(key);
      }
    }
  }
}

void processNumberKey(char key) {
  lcd.setCursor(a, 1);
  lcd.print("*");
  a++;
  if (a == 11) {
    a = 5;
  }
  currentPasswordLength++;
  password.append(key);

  if (currentPasswordLength == maxPasswordLength) {
    if (password.evaluate()) {
      unlockDoor();
      lockDoor();
    } else {
      invalidPasswordAlert();
    }
    resetPassword();
  }
}

void lockDoor() {
  servo1.write(0); // Lock position
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
  lcd.setCursor(0, 0);
  lcd.print("DOOR LOCKED");
  delay(2000);
  lcd.clear();
  doorLocked = true;
  ultrasonicEnabled = false; // Disable ultrasonic sensor
}

void unlockDoor() {
  if (password.evaluate()) {
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    servo1.write(95);
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("CORRECT PASSWORD");
    lcd.setCursor(0, 1);
    lcd.print("OPEN THE DOOR...");
    delay(2000);
    lcd.clear();
    doorLocked = false;
    ultrasonicEnabled = true; 
    a = 5;
  } else {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("WRONG PASSWORD!");
    lcd.setCursor(0, 1);
    lcd.print("PLEASE TRY AGAIN");
    delay(2000);
    lcd.clear();
    a = 5;
  }
  resetPassword();
}

void resetPassword() {
  password.reset();
  currentPasswordLength = 0;
  lcd.clear();
  a = 5;
}

void invalidPasswordAlert() {
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  lcd.setCursor(0, 0);
  lcd.print("WRONG PASSWORD!");
  lcd.setCursor(0, 1);
  lcd.print("TRY AGAIN");
  delay(2000);
  lcd.clear();
}

bool checkUltrasonicSensor() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Debug: Print distance readings
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= lockDistance) {
    Serial.println("Object detected: Triggering lock!");
    return true;
  }
  return false;
}

void intruderAlert() {
  if (!doorLocked) { // Only lock the door if it isn't already locked
    lockDoor();
  }
  // Alert the user
  digitalWrite(buzzer, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INTRUDER ALERT");
  delay(10000); 
  digitalWrite(buzzer, LOW);
  lcd.clear();
}