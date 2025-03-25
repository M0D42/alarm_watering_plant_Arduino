#include <RTClib.h>
#include <Wire.h>

// Water pump motor pins
#define motorA 8
#define MotorB 9

// RTC timer and when it should activate
int alarm1 = 16;  // Hour to activate the water pump
RTC_DS3231 rtc;
int counter = 0;

// Time parameters
int minutes = 60000;
int seconds = 1000;
int delayX = 6 * seconds;

// Day of the week for the pump to activate (0=Sunday, 1=Monday, ..., 6=Saturday)
int targetDay = 3; // Set this to the desired day (e.g., 3 for Wednesday)

void waterpump() {
  Serial.println("Waterpump function on");
  digitalWrite(motorA, HIGH);
  delay(delayX);
  digitalWrite(motorA, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(motorA, OUTPUT);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.print("failed connection");
    Serial.flush();
    while (1) delay(10);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Sync RTC

  delay(1000);
  Serial.println("End setup");
}

void loop() {
  // Get current time
  DateTime time1 = rtc.now();

  // Check if it's the correct day and the correct hour to activate the pump
  if (alarm1 == time1.hour() && targetDay == time1.dayOfTheWeek() && counter == 0) {
    waterpump();
    counter++;  // Ensure it only runs once per activation
  }

  // Reset the counter if the time isn't the alarm time or the day isn't the target day
  if (alarm1 != time1.hour() || targetDay != time1.dayOfTheWeek()) {
    counter = 0;
  }
}
