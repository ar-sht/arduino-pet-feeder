#include <Servo.h>
#include <TimeLib.h>

Servo myservo;
long duration, distance;

String incomingString;
time_t currentTime;

time_t setCurrentTime(String timeString);
void runScheduled(String time1, String time2, String time3, time_t t);
void runAutomatically();
void feed();
String convert(int time);

void setup() {
  pinMode(12, OUTPUT); // LED
  
  pinMode(5, OUTPUT); // distance sensor
  pinMode(7, INPUT);
  
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
  while(Serial.available() <= 0) {
    digitalWrite(5, HIGH);
    delay(10);
    digitalWrite(5, LOW);

    duration = pulseIn(7, HIGH);

    distance = duration/58;


    if (distance < 10 && distance > 0) {
      feed();
    }
  }

  incomingString = Serial.readString();
  incomingString.trim();
  if (incomingString.startsWith("S")) {
    currentTime = setCurrentTime(incomingString.substring(1));
  }
  else if (incomingString.startsWith("F")) {
    runScheduled(incomingString.substring(1, 6), incomingString.substring(6, 11), incomingString.substring(11), currentTime);
  } 
  if (incomingString.startsWith("O")) feed();
}

time_t setCurrentTime(String timeString) {
  int current_hour = timeString.substring(0, 2).toInt();
  int current_minute = timeString.substring(2, 4).toInt();
  setTime(current_hour, current_minute, 0, 1, 1, 23);
  time_t t = now();
  Serial.println("time set");
  return t;
}

void runScheduled(String time1, String time2, String time3, time_t t) {
  int timesFed = 0;

  String current_hour;
  String current_minute;

  String hour1 = (String) time1.substring(0, 2);
  String minute1 = (String) time1.substring(3);
  String hour2 = (String) time2.substring(0, 2);
  String minute2 = (String) time2.substring(3);
  String hour3 = (String) time3.substring(0, 2);
  String minute3 = (String) time3.substring(3);
  Serial.println("feeding times set");

  while (true) {
    current_hour = convert(hour(t));
    current_minute = convert(minute(t));
    Serial.print(current_hour);
    Serial.print(":");
    Serial.println(current_minute);
    if (current_hour == hour1 && current_minute == minute1 || 
    current_hour == hour2 && current_minute == minute2 || 
    current_hour == hour3 && current_minute == minute3) {
      Serial.println("made it!");
      feed();
      timesFed += 1;
      if (timesFed == 3) {
        Serial.println("schedule completed");
        break;
      }
    } 
    else if (current_hour != hour1 && current_hour != hour2 && current_hour != hour3) delay(59 * 60000);
    delay(60000);
  }
}

void runAutomatically() {
}

void feed() {
  myservo.write(80);
  digitalWrite(12, HIGH);
  delay(200);
  myservo.write(0);
  digitalWrite(12, LOW);
  delay(1000);
}

String convert(int time) {
  if (time < 10) return "0" + (String) time;
  else return (String) time;
}
