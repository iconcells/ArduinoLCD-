/*
 WiFi InOut weather by Kenneth Ng
 
 (using Repeating Wifi Web Client code base )
 This sketch connects to a a web server and makes a request
 using an Arduino Wifi shield.

 Circuit:
 * WiFi shield attached to pins SPI pins and pin 7

 created 23 April 2012
 modified 31 May 2012
 by Tom Igoe
 modified 13 Jan 2014
 by Federico Vanzati

 http://www.arduino.cc/en/Tutorial/WifiWebClientRepeating
 This code is in the public domain.
 */

#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include <aJSON.h>
#include "rgb_lcd.h"
#include <Servo.h> 

Servo myservo; 

rgb_lcd lcd;
char ssid[] = "iconpath5";      //  your network SSID (name)
char pass[] = "1122CC4455";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

const int MAXBUFFER = 3072;
static char stringBuffer[MAXBUFFER];
const int B = 3975;           // Define the B-value of the thermistor for Grove - Temperature Sensor
const int pinTemp = A0;       // Sensor addr
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

const int buttonPin = 4;
const int motorPin = 3; 
int potpin = 3;  // analog pin used to connect the potentiometer
int valpotpin;    // variable to read the value from the analog pin 

int status = WL_IDLE_STATUS;
// Initialize the Wifi client library
WiFiClient client;

// server address:
char server[] = "api.wunderground.com";

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
//Button n Moter
  pinMode(buttonPin,INPUT);
  myservo.attach(motorPin);  // attaches the servo on pin 3 to the servo object 

//LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

//WIFI
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    lcd.print("Please upgrade firmware");
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Trying SSID: ");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
    
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
      
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

  // list indoor sensor every minute
  for (int n=1;n<60; n++){
    printSensorWeather();
    delay(1000);          // wait 1 seconds, for sensor, 60 for connection:
    
    // Moter
    motor();
  }
}

void motor(){
  valpotpin = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  valpotpin = map(valpotpin, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(valpotpin);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();
    
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /api/5308b74281bc8781/conditions/q/CA/South_San_Francisco.json HTTP/1.1");
    client.println("Host: api.wunderground.com");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
    printWeatherLCD();
  } else {
    // if you couldn't make a connection:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("connect Err.. ");
    Serial.println("connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void printWeatherLCD(){

  // if there are incoming bytes available 
  // from the server, read them and print them:
  boolean jsonFound = false;
  int bytes = 0;
  while (client.available()) {
    //lcd.print("reading...");

    char c = client.read();
    //look for first {, yes it could be in a cookie but I'm thinking positively.
    if (c == '{') jsonFound = true;
    if (!jsonFound) continue;
  
    stringBuffer[bytes++] = c;
    if (bytes >= MAXBUFFER) break; //that's all we have room for or we're done
  }
  
  Serial.write(stringBuffer);
  aJsonObject* root = aJson.parse(stringBuffer);

  // kk weather printing code
   
  if (root != NULL) {
    aJsonObject* bgs = aJson.getObjectItem(root, "current_observation");
    if (bgs != NULL) {
        aJsonObject* sgv = aJson.getObjectItem(bgs, "display_location");
        aJsonObject* where = NULL;
        if (sgv != NULL){
          where = aJson.getObjectItem(sgv, "city");
        }
          
        aJsonObject* sge = aJson.getObjectItem(bgs, "temperature_string");
        aJsonObject* localT = aJson.getObjectItem(bgs, "local_time_rfc822");
        String bg = sge->valuestring;
        String whereStr = where->valuestring;
        String localTStr = localT->valuestring;
        
        //float bgfloat = bg.tofloat();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SSF");
        lcd.setCursor(4, 0);
        lcd.print(localTStr.substring(0,3));
        lcd.setCursor(8, 0);
        lcd.print(localTStr.substring(5,7));
        lcd.setCursor(11, 0);
        lcd.print(localTStr.substring(17,22));
        lcd.setCursor(0, 1);
        lcd.print(bg.substring(0,7));

    } 
  }
  memset(stringBuffer, 0, sizeof(stringBuffer));
}

// Indoor temperature in F, and change LCD bg color
void printSensorWeather(){

  int val = analogRead(pinTemp);     // Get the (raw) value of the temperature sensor.
  
  // Determine the current resistance of the thermistor based on the sensor value.
  float resistance = (float)(1023-val)*10000/val;

  // Calculate the temperature based on the resistance value.
  float temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;
  float F = temperature * 1.8 + 32;

  // Print the temperature to the serial console.
  //Serial.println(temperature);

  // Change background color 
  if (F > 68){
    lcd.setRGB(colorR, colorG, colorB);
  } else if (F > 61 ){
    lcd.setRGB(0, 255, 0);
  } else {
    lcd.setRGB(0, 0, 255);
  }
  
  lcd.setCursor(7, 1);
  lcd.print("Rm");
  lcd.setCursor(10, 1);
  lcd.print(F);
  lcd.setCursor(15, 1);
  lcd.print("F");
}
