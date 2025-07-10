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

| LCD Pin | 74HC595 Shift Register | Description                                                                                                                          |
|---------|-----------------------|--------------------------------------------------------------------------------------------------------------------------------------|
| RS      | Q0                    | Register Select                                                                                                                      |
| E       | Q1                    | Enable                                                                                                                               |
| D4      | Q2                    | Data 4                                                                                                                               |
| D5      | Q3                    | Data 5                                                                                                                               |
| D6      | Q4                    | Data 6                                                                                                                               |
| D7      | Q5                    | Data 7                                                                                                                               |
| VSS     | GND                   | Ground                                                                                                                               |
| VDD     | 5V                    | Power                                                                                                                                |
| VO      | Potentiometer         | Contrast control                                                                                                                     |
| RW      | GND                   | Tying to Ground or 0, puts it in Write only mode (If RW is set to 1, it puts it in read mode but this library does not support that) |
| A / K   | 5V / GND              | Backlight (+/-)                                                                                                                      |

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
4-bit mode. Every program has to start with `(your object name here).begin();`

#### begin() example ####
```
#include <lcd595.h>

LCD595 lcd(2, 4, 3);

void setup() {
    lcd.begin();
    lcd.print("Hello, world!");
}

void loop() {}
```
### Code Run-Through ###
1. First we have to instruct the compliler to include the contents of `lcd595.h` whcih contains the 
class definition for `LCD595`, without this
the compiler will not recognize `LCD595` as a valid type.
```
#include <lcd595.h>
```
2. This line instantiates an object of teh `LCD595` class and names it `lcd`. 
The class constructor `LCD595::LCD595(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin)`
is invoked with the arguments `2`, `4`, and `3`. These values initialize the private member
variables `_dataPin`, `_clockPin`, and `_latchPin` within the `lcd` object. The object, `lcd`, now encapsulates
the states and methods required for all the following hardware interactions.
```
LCD595 lcd(2, 4, 3);
```
3. This line calls the `begin()` member function on the object we named `lcd`. This function handles
low-level hardware and controller initialization. It uses the arduino's built-in `pinMode()` function that
sets the `data`, `clock`, and `latch` pins as `OUTPUT`. 
```aiignore
lcd.begin();
```
4. The print method passes a string literal (`const char*`), which the method then iterates through each
character in the character array until it reaches a `\0` null terminator. For each character, the method 
invokes the `write()` method. The `write()` method sends the characters's 8 bit ASCII value by setting 
the **RS (Register Select)** pin to high and then sending the high and low nibbles of the byte to the 
display. 
```aiignore
lcd.print("Hello, world!");
```
### 
