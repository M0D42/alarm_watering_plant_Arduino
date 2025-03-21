#include <RTClib.h>
#include <Wire.h>

//waterpump motor 
#define motorA 3
#define MotorB 4
//rtc timer and when it should activate
int alarm1 = 8;
RTC_DS3231 rtc;
int counter = 0;
//what happen when you do the water
int minutes = 60000;
int secondes = 1000;
int delayX = 1 * minutes;

 void waterpump(){
  Serial.println("Waterpump funcion on");
  digitalWrite(motorA, 1);
  delay(delayX);
  digitalWrite(motorA, 0);
 }

void setup() {

  Serial.begin(9600);
  pinMode(motorA, OUTPUT);

//real time clock activared 
rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Sync RT
    if (!rtc.begin()) {
        Serial.print("failed connection");
        Serial.flush();
        while (1) delay(10);
    }
    
Serial.println("end setup");
}

void loop() {
  //make time1 into and rtc funcion
    DateTime time1 = rtc.now();
  //Only activarws when the the hour is the alarm and it has not happen before
    if (alarm1 == time1.hour() && counter == 0) {
      waterpump();
      //this make it only happen once
        counter++;
         
    }
    //this recest the counter when the time isnt the alarm
    if (alarm1 != time1.hour()) {
        counter = 0;
    }
}
