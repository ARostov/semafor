#ifndef _SUNCHISE_LED_H_
#define _SUNCHISE_LED_H_
#include <Arduino.h>

enum LedStatus {
    ON, OFF, PROCESS
};

class Led {
private:
    int pin;
    float slowSwitchValue = 300;
    const int slowSwitchStepCount = 25;

    int tickInterval = 1000 / slowSwitchStepCount;
    uint32_t lastTickTime = 0;

    int riseMode = 0;

    LedStatus status = OFF;

    const float MAX_ANALOG_VALUE = 255.0;

    bool isTickReady() const {
        return (millis() - lastTickTime) >= tickInterval;
    }

public:
    explicit Led(int pin) {
        this->pin = pin;
        Serial.begin(9600);
        pinMode(pin, OUTPUT);
    }

    void tick() {
        Serial.print(riseMode);
        Serial.print(" - ");
        Serial.println(slowSwitchValue);
        if (riseMode != 0 && isTickReady()) {
            slowSwitchValue += riseMode * MAX_ANALOG_VALUE / slowSwitchStepCount;
            if (slowSwitchValue > MAX_ANALOG_VALUE) {
                slowSwitchValue = MAX_ANALOG_VALUE;
            }
            if (slowSwitchValue < 0) {
                slowSwitchValue = 0;
            }
            analogWrite(pin, slowSwitchValue);
            Serial.print(millis());Serial.print(" - ");Serial.println(slowSwitchValue);
            if (slowSwitchValue <= 0) {
                riseMode = 0;
                status = OFF;
            }
            if (slowSwitchValue >= MAX_ANALOG_VALUE) {
                riseMode = 0;
                status = ON;
            }
            lastTickTime = millis();
        }
    }

    void on() {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, true);
        status = ON;
    }

    void off() {
        digitalWrite(pin, false);
        status = OFF;
    }

    void slowOn(const int riseTime = 200) {
        slowSwitchValue = 0;
        riseMode = +1;
        tickInterval = riseTime / slowSwitchStepCount;
        status = PROCESS;
    }

    void slowOff(const int dropTime = 200) {
        slowSwitchValue = MAX_ANALOG_VALUE;
        riseMode = -1;
        tickInterval = dropTime / slowSwitchStepCount;
        status = PROCESS;
    }

    LedStatus getStatus() const {
        return status;
    }
};

#endif //_SUNCHISE_LED_H_
