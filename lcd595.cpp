#include "lcd595.h"

LCD595::LCD595(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin)
  : _dataPin(dataPin), _clockPin(clockPin), _latchPin(latchPin) {}

void LCD595::begin() {
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);

    delay(50); // Wait for LCD to power up

    // LCD init sequence (4-bit mode)
    sendNibble(0x03, false);
    delay(5);
    sendNibble(0x03, false);
    delayMicroseconds(150);
    sendNibble(0x03, false);
    sendNibble(0x02, false); // Set 4-bit mode

    // Function set: 4-bit, 2 line, 5x8
    command(0x28);
    // Display ON, cursor OFF, blink OFF
    command(0x0C);
    // Clear display
    command(0x01);
    delay(2);
    // Entry mode set: left to right
    command(0x06);
}

void LCD595::shiftOutByte(uint8_t data) {
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, MSBFIRST, data);
    digitalWrite(_latchPin, HIGH);
}

uint8_t createShiftByte(uint8_t nibble, bool isData) {
    uint8_t data = (nibble & 0x0F) << 2; // D4–D7 = Q2–Q5
    if (isData) data |= (1 << 0);        // RS = Q0
    return data;
}

void LCD595::pulseEnable(uint8_t data) {
    shiftOutByte(data & ~(1 << 1)); // E = 0
    delayMicroseconds(1);
    shiftOutByte(data | (1 << 1));  // E = 1
    delayMicroseconds(1);
    shiftOutByte(data & ~(1 << 1)); // E = 0
    delayMicroseconds(100);
}

void LCD595::sendNibble(uint8_t nibble, bool isData) {
    uint8_t data = createShiftByte(nibble, isData);
    pulseEnable(data);
}

void LCD595::sendByte(uint8_t byteVal, bool isData) {
    sendNibble(byteVal >> 4, isData);
    sendNibble(byteVal & 0x0F, isData);
}

void LCD595::command(uint8_t cmd) {
    sendByte(cmd, false);
}

void LCD595::write(uint8_t chr) {
    sendByte(chr, true);
}

void LCD595::clear() {
    command(0x01);
    delay(2);
}

void LCD595::print(const char* str) {
    while (*str) {
        write(*str++);
    }
}
