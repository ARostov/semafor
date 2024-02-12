//
// Created by  Александр on 09.02.2024.
//

#ifndef SEVENSEGMENTDISPLAY_H
#define SEVENSEGMENTDISPLAY_H


class SevenSegmentDisplay {
    const int digitPins[17][8] = {
        {1, 1, 1, 1, 1, 1, 0, 0}, //0
        {0, 1, 1, 0, 0, 0, 0, 0}, //1
        {1, 1, 0, 1, 1, 0, 1, 0}, //2
        {1, 1, 1, 1, 0, 0, 1, 0}, //3
        {0, 1, 1, 0, 0, 1, 1, 0}, //4
        {1, 0, 1, 1, 0, 1, 1, 0}, //5
        {1, 0, 1, 1, 1, 1, 1, 0}, //6
        {1, 1, 1, 0, 0, 0, 0, 0}, //7
        {1, 1, 1, 1, 1, 1, 1, 0}, //8
        {1, 1, 1, 1, 0, 1, 1, 0}, //9
        {0, 0, 0, 0, 0, 0, 0, 0}, // empty
        {0, 0, 0, 0, 0, 0, 1, 0}, // -
        {0, 0, 0, 0, 0, 0, 0, 1}, // .
        {1, 0, 0, 1, 1, 1, 1, 0}, // E
        {0, 0, 0, 0, 1, 1, 1, 0}, // r
        {1, 1, 1, 0, 1, 1, 1, 0}, // A
        {1, 1, 0, 0, 1, 1, 1, 0} // P
    };

    char value = 0;
    int pins[8];
    bool uniAnod = true;

    int charToIndex(const char symbol) const {
        switch (symbol) {
            case '0': return 0;
                break;
            case '1': return 1;
                break;
            case '2': return 2;
                break;
            case '3': return 3;
                break;
            case '4': return 4;
                break;
            case '5': return 5;
                break;
            case '6': return 6;
                break;
            case '7': return 7;
                break;
            case '8': return 8;
                break;
            case '9': return 9;
                break;
            case ' ': return 10;
                break;
            case '-': return 11;
                break;
            case '.': return 12;
                break;
            case 'E': return 13;
                break;
            case 'r': return 14;
                break;
            case 'A': return 15;
                break;
            case 'P': return 16;
                break;
            default: return 10;
        }
    }

public:
    SevenSegmentDisplay(const int pin_a, const int pin_b, const int pin_c, const int pin_d, const int pin_e,
                        const int pin_f, const int pin_g, const int pin_dp, bool uniAnod = true)
        : pins{pin_a, pin_b, pin_c, pin_d, pin_e, pin_f, pin_g, pin_dp} {
        for (int i = 0; i < 8; ++i) {
            pinMode(pins[i], OUTPUT);
        }
    }

    char getValue() const {
        return value;
    }

    void setValue(const char symbol) {
        Serial.print("Symbol: ");Serial.println(symbol);
        value = symbol < 0 ? 0 : symbol;
        int intValue = charToIndex(symbol); //value & 0xF;
        for (int pinIndex = 0; pinIndex < 8; ++pinIndex) {
            digitalWrite(pins[pinIndex], uniAnod != digitPins[intValue][pinIndex]);
        }
    }
};


#endif //SEVENSEGMENTDISPLAY_H
