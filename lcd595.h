#ifndef LCD595_H
#define LCD595_H

#include <Arduino.h>

class LCD595 {
public:
    LCD595(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin);
    void begin();
    void clear();
    void print(const char* str);
    void setCursor(uint8_t col, uint8_t row);
    void command(uint8_t cmd);
    void write(uint8_t chr);

private:
    void shiftOutByte(uint8_t data);
    void sendNibble(uint8_t nibble, bool isData);
    void sendByte(uint8_t byteVal, bool isData);
    void pulseEnable(uint8_t data);

    uint8_t _dataPin, _clockPin, _latchPin;
};

#endif
