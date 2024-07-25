#define enA 3
#define in1 8
#define in2 7
#define enB 6
#define in3 4
#define in4 5
#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1); // RX, TX
// Наші піни ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
String inputString = "";

int motorSpeedA = 140;
int motorSpeedB = 140;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600); // Ініціалізація апаратного серійного порту для Bluetooth
  mySerial.begin(9600); // Ініціалізація програмного серійного порту для Bluetooth

  Serial.println("Bluetooth Ready");
}

void loop() {
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');
    Serial.print("Received from Serial: ");
    Serial.println(inputString);
    handleInput(inputString);
  }

  if (mySerial.available() > 0) {
    inputString = mySerial.readStringUntil('\n');
    Serial.print("Received from Bluetooth: ");
    Serial.println(inputString);
    handleInput(inputString);
  }
}

// ВПЕРЕД ПОЧАТОК ------------------------------------------------------------------------------------------------------------------------------------------------------
void MoveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}

void MoveLeftForward() {
  int reducedSpeedA = motorSpeedA / 2;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enA, reducedSpeedA);
  analogWrite(enB, motorSpeedB);
}

void MoveRightForward() {
  int reducedSpeedB = motorSpeedB / 2;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, reducedSpeedB);
}
// ВПЕРЕД КІНЕЦЬ -------------------------------------------------------------------------------------------------------------------------------------------------------------

// СЕРЕДИНА ПОЧАТОК ---------------------------------------------------------------------------------------------------------------------------------------------------------------
void TurnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}

void TurnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}

void StopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void MoveBackward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}
// СЕРЕДИНА КІНЕЦЬ ---------------------------------------------------------------------------------------------------------------------------------------------------

// НАЗАД ПОЧАТОК ---------------------------------------------------------------------------------------------------------------------------------------------------------
void MoveLeftBackward() {
  int reducedSpeedA = motorSpeedA / 2;
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, reducedSpeedA);
  analogWrite(enB, motorSpeedB);
}

void MoveRightBackward() {
  int reducedSpeedB = motorSpeedB / 2;
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, reducedSpeedB);
}
// НАЗАД КІНЕЦЬ ----------------------------------------------------------------------------------------------------------------------------------------------------------

void setMotorSpeed(int speed) {
  motorSpeedA = constrain(speed, 0, 255);
  motorSpeedB = motorSpeedA;
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
}

void handleInput(String inputString) {
  inputString.trim(); // Remove any extra whitespace
  int command = inputString.toInt();

  switch(command) {
    case 1:
      MoveLeftForward();
      Serial.println("Moving Left Forward");
      break;
    case 2:
      MoveForward();
      Serial.println("Moving Forward");
      break;
    case 3:
      MoveRightForward();
      Serial.println("Moving Right Forward");
      break;
    case 4:
      TurnLeft();
      Serial.println("Turning Left");
      break;
    case 5:
      StopMotors();
      Serial.println("Stopping Motors");
      break;
    case 6:
      TurnRight();
      Serial.println("Turning Right");
      break;
    case 7:
      MoveLeftBackward();
      Serial.println("Moving Left Backward");
      break;
    case 8:
      MoveBackward();
      Serial.println("Moving Backward");
      break;
    case 9:
      MoveRightBackward();
      Serial.println("Moving Right Backward");
      break;
    default:
      Serial.println("Unknown Command");
      break;
  }
}
