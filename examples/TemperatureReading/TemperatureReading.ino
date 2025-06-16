#include <lcd595.h>

#define TIME 1000

LCD595 lcd(2, 4, 3);

int tempPin = A1;

const int dataPin = 2;
const int latchPin = 3;
const int clockPin = 4;

int tempReading = 0;
double tempK = 0;
float tempC = 0;
float tempF = 0;

void readTemp(){
    // reads data from analog pin 0, the thermistor
    tempReading = analogRead(tempPin);
    // temperature calculated in Kelvin
    tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
    // using Kelvin temp, convert to Celsius
    tempC = tempK - 273.15;
    // convert from C to Fahrenheit
    tempF = (tempC * 9.0)/ 5.0 + 32.0;

    // user prompts in serial monitor for troubleshoooting
    Serial.print(tempC);
    Serial.println(" C");
    Serial.print(tempF);
    Serial.println(" F");

    delay(TIME);
}

void setup() {
    delay(15);
    pinMode(tempPin, INPUT);
    lcd.begin();
    lcd.print("Hello, world");
    Serial.begin(9600);
    Serial.println("Hello, world");
}

void loop() {
    readTemp();

    char stempF[7];
    char stempC[7];
    dtostrf(tempF, 6, 2, stempF);
    dtostrf(tempC, 6, 2, stempC);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(stempF);
    lcd.setCursor(7, 0);
    lcd.print("F");

    lcd.setCursor(0, 1);
    lcd.print(stempC);
    lcd.setCursor(7, 1);
    lcd.print("C");

}
