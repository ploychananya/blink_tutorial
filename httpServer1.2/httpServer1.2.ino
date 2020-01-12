#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


#ifndef STASSID
#define STASSID "AP"
#define STAPSK  "123456789"
#endif


int LED_BUILTIN_POWER = 0;
int LED_BUILTIN_DELAY = 1000;
const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = LED_BUILTIN; 

const String postForms = "<html>\
  <head>\
    <title>ESP8266 Web Server POST handling</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>POST plain text to /postplain/</h1><br>\
    <form method=\"post\" enctype=\"text/plain\" action=\"/postplain/\">\
      <input type=\"text\" name=\'{\"hello\": \"world\", \"trash\": \"\' value=\'\"}\'><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
    <h1>POST form data to /postform/</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\">\
      <input type=\"text\" name=\"hello\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
  </body>\
</html>";

void handleRoot() {
//  digitalWrite(led, 1);
  server.send(200, "text/html", postForms);
//  digitalWrite(led, 0);
}

int assign(int& px_dy, int in_px_dy ){
     px_dy = in_px_dy;
     return px_dy;
  }

          

void handleLed() {
  
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "POST form was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      Serial.println(server.argName(i));
        assign(LED_BUILTIN_POWER,server.arg(i).toInt());      
    }
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", message);
  }
}

void handleDelay() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "POST form was:\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      Serial.println(server.argName(i));
        assign(LED_BUILTIN_DELAY,server.arg(i).toInt());     
    }
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", message);
  }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/led/", handleLed);
  server.on("/delay/", handleDelay);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void led_process() {
    digitalWrite(led, LED_BUILTIN_POWER);
    delay(LED_BUILTIN_DELAY);
    digitalWrite(led, 0);
    delay(LED_BUILTIN_DELAY);

  }
void loop() {
  led_process();
  server.handleClient();
  
}
