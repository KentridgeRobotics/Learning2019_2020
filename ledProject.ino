const int greenLed = 3;
const int yellowLed = 5;
const int redLed = 6;
const int trig = 9;
const int echo = 10;
const int joystickX = A1;
const int joystickY = A2;
const int button = 7;

int brightness = 255;
long distance = 0;


// Arduino Nano: PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function
// my arduino nano clones: use "ATMega 328P (Old Bootloader)"

void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(button, INPUT);
}

// Returns distance in cm
long getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long echoTime = pulseIn(echo, HIGH);
  long distance = (echoTime/2) / 29.1;
  return distance;
}

int getJoystickY() {
  int voltage = analogRead(joystickY);
  if (voltage < 200) {
    return -1;
  }
  else if (voltage > 600) {
    return 1;
  }
  else {
    return 0;
  }
}

void loop() {
  int joyY = getJoystickY();
  if (joyY < 0 && brightness > 0) {
    brightness--;
  }
  else if (joyY > 0 && brightness < 255) {
    brightness++;
  }
  else {
    // dead zone
  }
  long currentDistance = getDistance();
  if (currentDistance != 0) {
    distance = currentDistance;
  }
  
  if (distance < 6) {
    analogWrite(redLed, brightness);
    analogWrite(yellowLed, 0);
    analogWrite(greenLed, 0);
  }
  else if (distance < 10) {
    analogWrite(redLed, 0);
    analogWrite(yellowLed, brightness);
    analogWrite(greenLed, 0);
  }
  else {
    analogWrite(redLed, 0);
    analogWrite(yellowLed, 0);
    analogWrite(greenLed, brightness);
  }
/*  Serial.print("joyY:");
  Serial.print(joyY);
  Serial.print(" brightness:");
  Serial.print(brightness);
  Serial.print(" distance:");
  Serial.println(distance);
  */
}