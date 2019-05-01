/// based on
/// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/examples/Authorization/Authorization.ino

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;


const char* ssid = "your ssid";
const char* password = "yout wifi password";
//int adc=0;
const char* host = "io.adafruit.com";
//char occupied[10]="value=";
//char message[10]="";
const char* io_key = "f1fe68f5c8b64699969045cfa55d135c";
const char* path_with_username = "/api/v2/youraccount/feeds/garbage/data";

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "77 00 54 2D DA E7 D8 03 27 31 23 99 EB 27 DB CB A5 4C 57 18";
const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

// defines variables
long duration;
int distance;
void setup() {
  Serial.begin(115200);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); 
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
String occupied="";
 digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

Serial.println(distance);
String message="value=";
//if (distance< 3) {
// occupied="full";}
// else
 //{
occupied=String(10-distance);
 //}
message=message + occupied;
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
  
  
