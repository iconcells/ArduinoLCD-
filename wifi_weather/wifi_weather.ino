#include <aJSON.h>
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
char ssid[] = "iconpath5"; //  your network SSID (name) 
char pass[] = "1122CC4455";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

const int MAXBUFFER = 3072;
static char stringBuffer[MAXBUFFER];

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "api.wunderground.com";    // name address for weather site (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;
int counter = 0;          // count how many times of Http request

byte Flat[8] = { 
  B00000,
  B01100,
  B00110,
  B11111,
  B11111,
  B00110,
  B01100,
  B00000
};

byte SingleUp[8] = {
  B00000,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00000
};

byte SingleDown[8] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000
};

byte FortyFiveUp[8] = {
  B00000,
  B01111,
  B00011,
  B00101,
  B01001,
  B10000,
  B00000,
  B00000
};

byte FortyFiveDown[8] = {
  B00000,
  B00000,
  B10000,
  B01001,
  B00101,
  B00011,
  B01111,
  B00000
};


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0, Flat);
  lcd.createChar(1, SingleUp);
  lcd.createChar(2, SingleDown);
  lcd.createChar(3, FortyFiveUp);
  lcd.createChar(4, FortyFiveDown);

  lcd.setCursor(0, 0);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    lcd.print("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0")
    lcd.print("Please upgrade firmware");

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Trying SSID: ");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 3 seconds for connection:
    lcd.setCursor(0, 0);
    lcd.print("Waiting...");
    delay(4000);
  }
  lcd.setCursor(0, 0);
  lcd.clear();
  printWifiStatus(); 
  
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Connecting... ");
  lcd.print(counter);

  if (client.connect(server, 80)) {
    lcd.clear();
    lcd.print("Server connected..");
    
    // Make a HTTP request:
    client.println("GET /api/5308b74281bc8781/conditions/q/CA/South_San_Francisco.json HTTP/1.1");
    client.println("Host: api.wunderground.com");
    client.println("Connection: close");
    client.println();
  } else {
    lcd.clear();
    lcd.print("Connect :( " );
    lcd.print(counter);
  }

  // if there are incoming bytes available 
  // from the server, read them and print them:
  boolean jsonFound = false;
  int bytes = 0;
  while (client.available()) {
    lcd.print("reading...");
    char c = client.read();
    //look for first {, yes it could be in a cookie but I'm thinking positively.
    if (c == '{') jsonFound = true;
    if (!jsonFound) continue;
  
    stringBuffer[bytes++] = c;
    if (bytes >= MAXBUFFER) break; //that's all we have room for or we're done
  }

  Serial.write(stringBuffer);

  aJsonObject* root = aJson.parse(stringBuffer);

    // kk code
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
          lcd.print(bg);
      } 
    }

//  if (root != NULL) {
//    aJsonObject* bgs = aJson.getObjectItem(root, "response");
//    if (bgs != NULL) {
//      aJsonObject* def = aJson.getArrayItem(bgs, 0);
//      if (def != NULL) {
//        aJsonObject* sgv = aJson.getObjectItem(def, "version");
//        String bg = sgv->valuestring;
//        int bgInt = bg.toInt();
//        if (bgInt > 180) lcd.setRGB(255, 0, 0);
//        if (bgInt > 150 && bgInt <= 180) lcd.setRGB(255, 255, 0);
//        if (bgInt <= 150) lcd.setRGB(0, 255, 0);
//        lcd.clear();
//        lcd.setCursor(0, 0);
//        lcd.print("City");
//        lcd.setCursor(0, 1);
//        lcd.print(bg);
//
//        lcd.setCursor(4, 1);
//
//        aJsonObject* direction = aJson.getObjectItem(def, "direction");
//        String dir = direction->valuestring;
//        
//        if (dir == "Flat") lcd.write(byte(0));
//        if (dir == "DoubleUp") {
//          lcd.write(byte(1)); lcd.write(byte(1));
//        }
//        if (dir == "SingleUp") lcd.write(byte(1));
//        if (dir == "FortyFiveUp") lcd.write(byte(3));
//        if (dir == "FortyFiveDown") lcd.write(byte(4));
//        if (dir == "SingleDown") lcd.write(byte(2));
//        if (dir == "DoubleUp") {
//          lcd.write(byte(2)); lcd.write(byte(2));
//        }
//      }
//    }
//  }

  memset(stringBuffer, 0, sizeof(stringBuffer));

  //delay(100000); //wait 100 sec
  delay(10000); 
  counter++;
  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    lcd.clear();
    lcd.println();
    lcd.print("disconnecting...");
    client.stop();

    // do nothing forevermore:
    //while (true);
    return; //start over!
  }
}




void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.print(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.print(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal (RSSI):");
  Serial.print(rssi);
  Serial.print(" dBm");
}

