#include <lcd595.h>

LCD595 lcd(2, 4, 3);

void setup() {
    lcd.begin();
    lcd.print("Hello, world!");
}

void loop() {}