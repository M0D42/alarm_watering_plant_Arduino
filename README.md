# Arduino Alarm Watering Plant System

This repository contains code for an Arduino-based watering system that uses a Real-Time Clock (RTC) to water plants at a specified time each day.

## Components

- Arduino board (e.g., Arduino Uno)
- Water pump motor
- RTC module (e.g., DS3231)
- L293D motor driver
- Wires and breadboard
- Power supply

## Wiring

- Connect the water pump motor to the L293D motor driver.
- Connect the L293D motor driver to digital pins 3 and 4 on the Arduino.
- Connect the RTC module to the I2C pins on the Arduino (SDA to A4, SCL to A5).

## Code Explanation

The code includes the following functionalities:

- Initialization of the water pump motor and RTC module.
- Setting up the RTC module to synchronize with the current date and time.
- Activating the water pump motor at a specific hour (defined by `alarm1` variable) for a defined duration (`delayX`).

### Code Breakdown

1. **Include Libraries**
    ```cpp
    #include <RTClib.h>
    #include <Wire.h>
    ```

2. **Define Motor Pins**
    ```cpp
    #define motorA 3
    #define MotorB 4
    ```

3. **RTC and Timing Variables**
    ```cpp
    int alarm1 = 8; // Hour at which the alarm will trigger
    RTC_DS3231 rtc;
    int counter = 0;
    int minutes = 60000;
    int seconds = 1000;
    int delayX = 1 * minutes; // Duration for which the water pump will run
    ```

4. **Water Pump Function**
    ```cpp
    void waterpump() {
        Serial.println("Waterpump function on");
        digitalWrite(motorA, 1);
        delay(delayX);
        digitalWrite(motorA, 0);
    }
    ```

5. **Setup Function**
    ```cpp
    void setup() {
        Serial.begin(9600);
        pinMode(motorA, OUTPUT);

        // Initialize the RTC module
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        if (!rtc.begin()) {
            Serial.print("failed connection");
            Serial.flush();
            while (1) delay(10);
        }

        Serial.println("end setup");
    }
    ```

6. **Loop Function**
    ```cpp
    void loop() {
        DateTime time1 = rtc.now();
        
        // Activate water pump at the specified hour
        if (alarm1 == time1.hour() && counter == 0) {
            waterpump();
            counter++;
        }
        
        // Reset counter when hour is not the alarm hour
        if (alarm1 != time1.hour()) {
            counter = 0;
        }
    }
    ```

## How to Use

1. Upload the code to the Arduino board.
2. Connect the hardware components as per the wiring instructions.
3. The water pump will activate at the specified hour (`alarm1` variable) each day for the duration defined by `delayX`.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
