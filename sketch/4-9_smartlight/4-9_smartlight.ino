#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h> //inclusion

ESP8266WebServer server(80);

String light_on = "1"; //the value for a on state
String light_off = "0"; //the value for a off state
String message = ""; //empty string, accepts client requests
String ssid_custome = "";//custome ssid
String password_custome = "";//custome PSK
const int led = 2; //define the pin where LED is pluged on esp8266
String request_url="";//custome location of the HTTP server
int commaPosition1=0;
int commaPosition2=0;
void handleNotFound() {
  Serial.println("Proccessing");
  message += server.uri(); //extract the ssid, password, request url from the GET request
  commaPosition1 = message.indexOf('=');
  commaPosition2 = message.indexOf('=',commaPosition1+1);
  if (commaPosition1!=0 && commaPosition2!=0){
  ssid_custome = message.substring(1, commaPosition1);
  password_custome = message.substring(commaPosition1 + 1, commaPosition2);
  request_url = message.substring(commaPosition2 + 1, message.length());//divide the message to there part by '='
  }
  delay(10);
  Serial.println(ssid_custome);//set the custome ssid
  Serial.println(password_custome);//set the custome password
  Serial.println(request_url);//set the custome password
  //server.send(200, "text/plain", ssid_custome);
}
void setup() {
  WiFi.mode(WIFI_AP); //switch the esp8266 to a Access Point
  WiFi.softAP("ESP8266");
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  Serial.println("AP established");//显示参数
  server.onNotFound(handleNotFound); //define the fonciton to use
  server.begin();//starting server on 192.168.4.1:80
  Serial.println("HTTP server started");
  Serial.println("Waiting");
  while (ssid_custome.length() == 0) {// if the custome ssid is not set
    server.handleClient();// listen to python clients.
  }

  WiFi.mode(WIFI_STA);//switch the esp8266 to a station
  WiFi.begin(ssid_custome.c_str(), password_custome.c_str()); //connect to Wi-Fi using ssid and password obtained form python clients
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");//wait for connection
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());//debug message
}

void loop() {
  //Serial.println(ssid_custome);
  //Serial.println(password_custome);
  delay(10); 
  // wait for WiFi connection

  HTTPClient http; //initialize a HTTP client

  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
  http.begin(request_url); //start a HTTP request to obtain the LED status form the server

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();//extract the status
      Serial.println(payload);
      if ( light_off == payload) {
        digitalWrite(2, LOW); // if the LED is set 'off'
        Serial.print("light is off");
      }

      if ( light_on == payload) {
        digitalWrite(2, HIGH);// if the LED is set 'on'
        Serial.print("light is on");
      }
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());//if the request failed
  }
  http.end();// end the http client
  delay(1000);//delay 1 second
}

