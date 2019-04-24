/// based on
/// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/Authorization/Authorization.ino

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "your ssid";
const char* password = "your wifi password";
int adc=0;
const char* host = "io.adafruit.com";
//char occupied[10]="value=";
//char message[10]="";
const char* io_key = "f1fe68f5c8b64699969045cfa55d135c";
const char* path_with_username = "/api/v2/youraccount/feeds/parking/data";
String occupied="free";

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "77 00 54 2D DA E7 D8 03 27 31 23 99 EB 27 DB CB A5 4C 57 18";

void setup() {
  Serial.begin(115200);

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

  adc=analogRead(A0);

String message="value=";
if (adc>10){
  Serial.println(adc);
  if (occupied=="free")
     occupied="occupied";
     else occupied="free";
message=message + occupied;
delay(100);
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
}
  
