//Thomas
#include <ESP8266WiFi.h>

const char* ssid = "Hermann P20";//type your ssid
const char* password = "abcd&Internet@4030";//type your password

/*const char* ssid = "e166";//type your ssid
const char* password = "Internet";//type your password*/
 
int ledPin = 0; // GPIO2 of ESP8266
int doorPin = 2;
WiFiServer server(80);
  
void setup() {
  delay(10);
  Serial.begin(9600);
  pinMode(ledPin, INPUT);
  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  /*IPAddress ip(192,168,0,230);   
  IPAddress gateway(192,168,0,1);   
  IPAddress subnet(255,255,255,0);   
  //WiFi.config(ip, gateway, subnet);*/
    IPAddress ip(192,168,2,200);   
  IPAddress gateway(192,168,2,254);   
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

  if (request.indexOf("/status") != -1) {
    client.println(digitalRead(ledPin));
  } 
  else if (request.indexOf("/toggle") != -1) {
    digitalWrite(doorPin, HIGH);
    delay(800);
    digitalWrite(doorPin, LOW);
    client.println("toggle");
  } 
  else if (request.indexOf("/") != -1) {
    String htmlCode = "<html><head> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Document</title> <link href='https://raw.githubusercontent.com/MrATBukkit/doorControl/master/style.css' rel='stylesheet'></head><body> <div class='container'> <button class='btn btn-danger btn-circle btn-xl status' id='toggle'>Schalten</button> </div></body><script src='https://cdnjs.cloudflare.com/ajax/libs/axios/0.18.0/axios.js'></script><script src='https://raw.githubusercontent.com/MrATBukkit/doorControl/master/jsscript.js'></script></html>";
    client.println(htmlCode);
  }
  // Return the response 
  delay(1);
 
} 
