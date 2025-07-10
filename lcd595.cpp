#include "lcd595.h"

// Constructor for LCD595 class, creates a new LCD595 object and stores the pin numbers that will be used to communicate with the shift register.
LCD595::LCD595(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin)
  // member initializer list, sets the initial values of the class's private variables
  : _dataPin(dataPin), _clockPin(clockPin), _latchPin(latchPin) {}

// initializes the LCD object and sets the defined pins as outputs.
void LCD595::begin() {
    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);

    // the following sequence of commands is the get the LCD ready to recieve and display text using 4-bit mode as defined in the datasheet
    delay(50); // Wait for LCD to power up

    // LCD init sequence (4-bit mode), data will be sent in nibbles instead of a whole byte at once
    // the sequence involves sending the value 0x03, which is 0 3, or 0000 0011, or 00000011
    // it sends 0x03 three times, along with the false argument (this indicates this is a command and NOT character data
    // After sending 0x03 three times, it sends 0x02 once which sets it to 4 bit mode regardless of its previous state
    sendNibble(0x03, false);
    delay(5);
    sendNibble(0x03, false);
    delayMicroseconds(150);
    sendNibble(0x03, false);
    sendNibble(0x02, false); // Set 4-bit mode

    // Once the LCD is in 4-bit mode, the begin function then sends full byte commands to configure its setting according to the datasheet
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

void LCD595::setCursor(uint8_t col, uint8_t row) {
    static const uint8_t rowOffsets[] = {0x00, 0x40};
    if (row > 1) row = 1; // clamp to 2-line display since this is a 1602 module
    command(0x80 | (col + rowOffsets[row]));
}
