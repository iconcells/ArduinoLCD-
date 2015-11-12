// Need to finish the display
// Wifi is connected

#include <Wire.h>
#include "rgb_lcd.h"
#include <WiFi.h>
#include <SPI.h>
#include "RestClient.h"

char ssid[] = "iconpath5";            //  your network SSID (name)
char pass[] = "1122CC4455";         // your network password
char host[] = "api.wunderground.com";      // target for your REST queries
int status = WL_IDLE_STATUS;         // the Wifi radio's status

// Create your WiFi RestClient, pass in the ssid and password.
RestClient client = RestClient(host, ssid, pass);


//------ LCD
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

//------

String response;
void setup() {

  // Initiate Serial Connection
  Serial.begin(9600);
  Serial.println("Starting REST client over Wi-Fi");
  if(client.connect() == WL_CONNECTED){
    response = "";
    int statusCode = client.get("/api/5308b74281bc8781/conditions/q/CA/San_Francisco.json", &response);
    Serial.print("Status code from server: ");
    Serial.println(statusCode);
    Serial.print("Response body from server: ");
    Serial.println(response);

    //-----
    lcd.clear();
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
    lcd.print("Weather Now:");
    //-----
    delay(1000);
  }
}

void loop(){
  //LCD
  float F = 22.22 * 1.8 + 32;
  
  lcd.setRGB(colorR, colorG, colorB); 
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(F,2);

  // Wait one second between measurements.
  delay(100);
}

