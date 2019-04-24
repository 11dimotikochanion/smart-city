/// based on
/// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/Authorization/Authorization.ino

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to


#define DHTTYPE DHT11 
ESP8266WiFiMulti WiFiMulti;
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "your ssid";
const char* password = "yout wifi password";

const char* host = "io.adafruit.com";

const char* io_key = "your adafruit io key";
const char* path_with_username = "/api/v2/youraccount/feeds/yourfeed/data";

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "77 00 54 2D DA E7 D8 03 27 31 23 99 EB 27 DB CB A5 4C 57 18";

void setup() {
  Serial.begin(115200);
    dht.begin();
 
  for(uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  // wait for WiFi connection
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  Serial.println("[WIFI] connected!");


 
}

void loop() {
    HTTPClient http;
String meteo="";
 delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
Serial.println(t);
Serial.println(h);
String message="value=";

meteo="temp="+String(t)+"hum="+String(h);

message=message + meteo;
delay(1000);
 // start request with URL and TLS cert fingerprint for verification
  http.begin("https://" + String(host) + String(path_with_username), fingerprint);

  // IO API authentication
  http.addHeader("X-AIO-Key", io_key);
  http.addHeader("Content-Type","application/x-www-form-urlencoded");
  // start connection and send HTTP header
  int httpCode = http.POST(message);
//String payload=http.getString();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET response: %d\n", httpCode);

    // HTTP 200 OK
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }

    http.end();
  }
}
  
  
