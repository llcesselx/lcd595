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

- Data → Arduino pin `2`
- Clock → Arduino pin `4`
- Latch → Arduino pin `3`

## 🔧 Installation

1. Download this repo as `.zip` or clone via Git:
   ```bash
   git clone https://github.com/llcesselx/LCD595.git
