#include <Servo.h>

Servo myservo;

int pos = 7;
int cm = 0;
int redLED = 12; // Pin for the red LED
int greenLED = 13; // Pin for the green LED

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() {
  pinMode(redLED, OUTPUT); // Set red LED pin as output
  pinMode(greenLED, OUTPUT); // Set green LED pin as output
  digitalWrite(redLED, LOW); // Initially turn off the red LED
  digitalWrite(greenLED, LOW); // Initially turn off the green LED
  myservo.attach(9); 
  Serial.begin(9600);
}

void loop() {
  cm = 0.01723 * readUltrasonicDistance(6, 7);

  if (cm < 10) {
    digitalWrite(redLED, HIGH); // Turn on red LED when barrier is down
    digitalWrite(greenLED, LOW); // Turn off green LED
    Serial.print(cm);
    Serial.println("cm");

    for (pos = 0; pos <= 60; pos += 1) { 
      myservo.write(pos);
      delay(15);
    }
    delay(500);

    for (pos = 60; pos >= 0; pos -= 1) { 
      myservo.write(pos);
      delay(15);
    }
    delay(15);
  } else {
    digitalWrite(redLED, LOW); // Turn off red LED when barrier is up
    digitalWrite(greenLED, HIGH); // Turn on green LED
  }
}