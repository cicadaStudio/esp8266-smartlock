#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>//inclusion
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

String light_on = "1";
String light_off = "0";
String message = "";
String ssid_custome = "";
String password_custome = "";
const int led = 2;
String request_url="";


int commaPosition1=0;
int commaPosition2=0;
void handleNotFound() {
  Serial.println("Proccessing");
  message += server.uri();
  commaPosition1 = message.indexOf('=');
  commaPosition2 = message.indexOf('=',commaPosition1+1);
  if (commaPosition1!=0 && commaPosition2!=0){
  ssid_custome = message.substring(1, commaPosition1);
  password_custome = message.substring(commaPosition1 + 1, commaPosition2);
  request_url = message.substring(commaPosition2 + 1, message.length());
  }
  delay(10);
  Serial.println(ssid_custome);
  Serial.println(password_custome);
  Serial.println(request_url);
  server.send(200, "text/plain", ssid_custome);
}
void setup() {
  WiFi.mode(WIFI_AP); //AP 模式
  WiFi.softAP("ESP8266");
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  Serial.println("AP established");//显示参数
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Waiting");
  while (ssid_custome.length() == 0) {
    server.handleClient();
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_custome.c_str(), password_custome.c_str());
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println(ssid_custome);
  Serial.println(password_custome);
  delay(10);
  // wait for WiFi connection

  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
  http.begin(request_url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
      if ( light_off == payload) {
        digitalWrite(2, LOW);
        Serial.print("light is off");
      }

      if ( light_on == payload) {
        digitalWrite(2, HIGH);
        Serial.print("light is on");
      }
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  delay(1000);
}

