// Temperature by Kenneth Ng
//
// Reads the value of the Grove - Temperature Sensor, converts it to a Celsius temperature,
// and prints it to the serial console.
// Connect the Grove - Temperature Sensor to the socket marked A0
// Open the Serial Monitor in the Arduino IDE after uploading

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

// Define the pin to which the temperature sensor is connected.
const int pinTemp = A0;

// Define the B-value of the thermistor.
// This value is a property of the thermistor used in the Grove - Temperature Sensor,
// and used to convert from the analog value it measures and a temperature value.
const int B = 3975;

void setup()
{
    // Configure the serial communication line at 9600 baud (bits per second.)
    Serial.begin(9600);

    lcd.clear();
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("Good day !!");

    delay(1000);
}

void loop()
{
    // Get the (raw) value of the temperature sensor.
    int val = analogRead(pinTemp);

    // Determine the current resistance of the thermistor based on the sensor value.
    float resistance = (float)(1023-val)*10000/val;

    // Calculate the temperature based on the resistance value.
    float temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;
    float F = temperature * 1.8 + 32;

    // Print the temperature to the serial console.
    Serial.println(temperature);

    // Change background color 
    if (F > 68){
      lcd.setRGB(colorR, colorG, colorB);
    } else if (F > 61 ){
      lcd.setRGB(0, 255, 0);
    } else {
      lcd.setRGB(0, 0, 255);
    }
    
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(F,2);

    // Wait one second between measurements.
    delay(100);
}

