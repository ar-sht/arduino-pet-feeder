#include <Servo.h>

Servo myservo;
long duration, distance;

int incomingByte;

void setup() {
  Serial.begin(9600);

  pinMode(12, OUTPUT); // LED
  
  pinMode(5, OUTPUT); // distance sensor
  pinMode(7, INPUT);
  
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }

  // put your main code here, to run repeatedly:
  digitalWrite(5, HIGH);
  delay(10);
  digitalWrite(5, LOW);

  duration = pulseIn(7, HIGH);

  distance = duration/58;

  if (distance < 20) {
    myservo.write(90);
    digitalWrite(12, HIGH);
    delay(500);
  }
  
  myservo.write(0);
  digitalWrite(12, LOW);

  delay(300000);
}
