#include <Servo.h>

const int SERVO = 7;
const int GREEN_LED_1 = 8;
const int YELLOW_LED_1 = 9;
const int RED_LED_1 = 10;
const int GREEN_LED_2 = 11;
const int YELLOW_LED_2 = 12;
const int RED_LED_2 = 13;

const int OFFSET = 40;
const int START_ANGLE = OFFSET;
const int FINISH_ANGLE = 180 - OFFSET;

Servo servo;
int servoAngle = 20;

void setup() {
  Serial.begin(9600);  
  servo.attach(SERVO);
  pinMode(GREEN_LED_1, OUTPUT);
  pinMode(YELLOW_LED_1, OUTPUT);
  pinMode(RED_LED_1, OUTPUT);
  pinMode(GREEN_LED_2, OUTPUT);
  pinMode(YELLOW_LED_2, OUTPUT);
  pinMode(RED_LED_2, OUTPUT);
}

void loop() {
  animate(); 
}

void turnOn(const int LED) {
  digitalWrite(LED, HIGH);
}

void turnOff(const int LED) {
  digitalWrite(LED, LOW);
}

void turnOffAll() {
  turnOff(GREEN_LED_1);
  turnOff(YELLOW_LED_1);
  turnOff(RED_LED_1);
  turnOff(GREEN_LED_2);
  turnOff(YELLOW_LED_2);
  turnOff(RED_LED_2);
}

void turnOnAll() {
  turnOn(GREEN_LED_1);
  turnOn(YELLOW_LED_1);
  turnOn(RED_LED_1);
  turnOn(GREEN_LED_2);
  turnOn(YELLOW_LED_2);
  turnOn(RED_LED_2);
}

void animate() {

  turnOffAll();

  //STEP 1: TURN ALL LIGHTS ON AND THEN OFF:
  turnOnAll();
  delay(50);
  
  //STEP 2: DO SEQUENTIAL ON/OFF:
  const int START_REPEATS = 3;  
  for (int repeats = 0; repeats < START_REPEATS; repeats++) {
  for (int i = GREEN_LED_1; i <= RED_LED_2; i++) {
    turnOn(i);
    delay(20);
    turnOff(i);
  }
  }
  
  turnOnAll();
  
  const int SERVO_DELAY = 50; //More is slower, less is faster.
 
  //STEP 3: TURN THE HEAD TO THE RIGHT:
  for(servoAngle = START_ANGLE; servoAngle < FINISH_ANGLE; servoAngle++) {                                  
    servo.write(servoAngle);
    delay(SERVO_DELAY);
  }

  //STEP 4: TURN ALL LIGHTS OFF:
  turnOffAll();
  
  //STEP 5: DO REVERSE SEQUENTIAL ON/OFF:
  const int END_REPEATS = 3;
  for (int repeats = 0; repeats < END_REPEATS; repeats++) {
  for (int i = RED_LED_2; i >= GREEN_LED_1; i--) {
    turnOn(i);
    delay(20);
    turnOff(i);
  }
  }
  
  turnOnAll();

  //STEP 6: TURN THE HEAD TO THE LEFT:
  for(servoAngle = FINISH_ANGLE; servoAngle > START_ANGLE; servoAngle--) {                                
    servo.write(servoAngle);
    delay(SERVO_DELAY);
  }
  
}
