# LCD595

An Arduino library for controlling a standard 1602 LCD module using a 74HC595 shift register. This library allows you to display text on the LCD using only 3 Arduino pins (data, clock, latch), freeing up valuable I/O.

## 📷 Overview

This library drives a 1602 (or compatible) character LCD by sending 4-bit data through a 74HC595 shift register. It minimizes pin usage by shifting out the required bits over SPI-style control.

## 🛠️ Features

- Minimal wiring — uses only 3 Arduino pins
- Supports standard 1602 LCD commands
- Simple API: `begin()`, `clear()`, `print()`, `command()`
- Easily expandable (`setCursor`, `createChar`, etc.)

## 📦 Requirements

- Arduino-compatible board (Nano, Uno, Mega, etc.)
- 1602 LCD module (HD44780-compatible)
- 74HC595 shift register
- Arduino IDE

## 🔌 Wiring

| LCD Pin | 74HC595 Output | Description        |
|---------|----------------|--------------------|
| RS      | Q0             | Register Select    |
| E       | Q1             | Enable             |
| D4      | Q2             | Data 4             |
| D5      | Q3             | Data 5             |
| D6      | Q4             | Data 6             |
| D7      | Q5             | Data 7             |
| VSS     | GND            | Ground             |
| VDD     | 5V             | Power              |
| VO      | Potentiometer  | Contrast control   |
| R/W     | GND            | Write only         |
| A/K     | 5V / GND       | Backlight (+/-)    |

**Arduino → 595 connections:**

- Data → Arduino pin `X` (pin 2)
- Clock → Arduino pin `Y` (pin 4)
- Latch → Arduino pin `Z` (pin 3)

- Replace `X`, `Y`, `Z` with your actual pin numbers when initializing.

## 🔧 Installation

1. Download this repo as `.zip` or clone via Git:
   ```bash
   git clone https://github.com/llcesselx/LCD595.git
   
## 😵 How to Use

### 4-Bit Initialization Mode `begin` Command

According to 1602 LCD Module Datasheets, the initialization sequence recommends giving the LCD
at least 40 ms to start up, when the LCD starts up, it starts in 8-bit mode by default. We
are only using 4 data pins and want to start the LCD in 4-bit mode. We have to do this
manually.

Sending the nibble `0x03` sends the bits `0011` to the LCD three times to ensure the LCD is fully
reset. When we send the fourth nibble `0x02`, we are sending the bits `0010` which sets it to
4-bit mode. Every program has to start with `(your initialization here).begin();`

```
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
```
   
### 
