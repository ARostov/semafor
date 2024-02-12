#include <Arduino.h>
#include <Led.h>
#include <GyverTimer.h>
#include <SevenSegmentDisplay.h>

Led ledRed = Led(A0);
Led ledYellow = Led(A1);
Led ledGreen = Led(A2);


int GREEN_TIME = 5000;
int GREEN_BLINK_TIME = 4000;
int YELLOW_TIME = 3000;
int RED_TIME = 5000;
int RED_N_YELLOW_TIME = 2000;

Led *leds[] = {&ledGreen, &ledRed, &ledYellow};

GTimer ledTimer;
GTimer display7Timer;

SevenSegmentDisplay dislay7 = SevenSegmentDisplay(2, 3, 4, 5, 6, 7, 8, 9);

enum Step {
    GREEN, GREEN_BLINK, YELLOW, RED, RED_N_YELLOW, YELLOW_BLINK
};

Step step = GREEN;
int tickCount = 0;


void offAllLeds() {
    for (int i = 0; i < sizeof leds; ++i) {
        leds[i]->off();
    }
}

void decDisplay7() {
    if (dislay7.getValue() > '1' && dislay7.getValue() <= '9') {
        dislay7.setValue(dislay7.getValue() - 1);
    }
}

char timeToSecChar(int ms) {
    return (ms / 1000) + '0';
}

void setup() {
    Serial.begin(9600);
    ledTimer.setMode(false);
    ledTimer.setTimeout(1);
    ledTimer.start();
    display7Timer.setInterval(1000);
    display7Timer.start();
    ledGreen.on();
    ledYellow.on();
    ledRed.on();
    dislay7.setValue('8');
    delay(300);
}

void loop() {
    if (ledTimer.isReady()) {
        switch (step) {
            case GREEN:
                offAllLeds();
                ledGreen.on();
                ledTimer.setTimeout(GREEN_TIME);
                dislay7.setValue(timeToSecChar(GREEN_TIME + GREEN_BLINK_TIME));
                display7Timer.start();
                step = GREEN_BLINK;
                break;
            case GREEN_BLINK:
                if (ledGreen.getStatus() == OFF) {
                    offAllLeds();
                    ledGreen.on();
                } else {
                    offAllLeds();
                }
                tickCount++;
                ledTimer.setTimeout(GREEN_BLINK_TIME / 8);
                if (tickCount > 8) {
                    tickCount = 0;
                    step = YELLOW;
                }
                break;
            case YELLOW:
                offAllLeds();
                ledYellow.on();
                ledTimer.setTimeout(YELLOW_TIME);
                dislay7.setValue(' ');
                step = RED;
                break;
            case RED:
                offAllLeds();
                ledRed.on();
                ledTimer.setTimeout(RED_TIME);
                dislay7.setValue(timeToSecChar(RED_TIME + RED_N_YELLOW_TIME));
                display7Timer.start();
                step = RED_N_YELLOW;
                break;
            case RED_N_YELLOW:
                offAllLeds();
                ledRed.on();
                ledYellow.on();
                ledTimer.setTimeout(RED_N_YELLOW_TIME);
                step = GREEN;
                break;
            default:
                break;
        }
    }
    if (display7Timer.isReady()) {
        if (dislay7.getValue() > '1' && dislay7.getValue() <= '9') {
            dislay7.setValue(dislay7.getValue() - 1);
        }
    }
}
