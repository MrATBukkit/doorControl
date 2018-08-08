//Thomas
#include <ESP8266WiFi.h>

const char* ssid = "Hermann P20";//type your ssid
const char* password = "abcd&Internet@4030";//type your password
 
int ledPin = 0; // GPIO2 of ESP8266
int doorPin = 2;
WiFiServer server(80);
  
void setup() {
  delay(10);
  Serial.begin(9600);
  pinMode(ledPin, INPUT);
  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);
   
  WiFi.begin(ssid, password);

  IPAddress ip(192,168,0,230);   
  IPAddress gateway(192,168,0,1);   
  IPAddress subnet(255,255,255,0);   
  //WiFi.config(ip, gateway, subnet);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Start the server
  server.begin();
  Serial.println("Server started"); 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');

  client.flush();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>"); 
  client.println("<html>");
  if (request.indexOf("/status") != -1) {
    client.println("Status: ");
    client.println(digitalRead(ledPin));
  } 
  if (request.indexOf("/toggle") != -1) {
    digitalWrite(doorPin, HIGH);
    delay(800);
    digitalWrite(doorPin, LOW);
    client.println("toggle");
  } 
  // Return the response 
  client.println("</html>");
  delay(1);
 
}
