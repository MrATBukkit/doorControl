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
    String htmlCode = "<!DOCTYPE html><html lang='de'><head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <meta http-equiv='X-UA-Compatible' content='ie=edge'> <link href='https://netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap.min.css' rel='stylesheet' id='bootstrap-css'> <title>Document</title> <style>.container{height: 100vh; padding: 0px; margin: 0px;}.btn-circle{width: 30px; height: 30px; text-align: center; padding: 6px 0; font-size: 12px; line-height: 1.428571429; border-radius: 15px; margin-left: 25vw; margin-top: calc((100vh - 50vw) / 2)}.btn-circle.btn-xl{width: 50vw; height: 50vw; padding: 10px 16px; font-size: 24px; line-height: 1.33; border-radius: 100px; margin-right: 50vw;}button{margin: 30px auto; text-align: center; display: flex; align-items: center; margin-bottom: 0px !important; margin-right: 0px !important;}</style></head><body> <div class='container'> <button class='btn btn-danger btn-circle btn-xl status' id='toggle'> Schalten </button> </div></body><script src='https://cdnjs.cloudflare.com/ajax/libs/axios/0.18.0/axios.js'></script><script>function setStatus(){axios.get('/status').then(function(response){document.querySelector('.status').innerHTML=response.data? 'Öffnen': 'Schließen'; if (response.data){document.querySelector('#toggle').classList.add('btn-danger'); document.querySelector('#toggle').classList.remove('btn-success');}else{document.querySelector('#toggle').classList.add('btn-success'); document.querySelector('#toggle').classList.remove('btn-danger');}}).catch(()=>{document.querySelector('.status').innerHTML='Fehler';});}setStatus(); setInterval(setStatus, 3000); document.querySelector('#toggle').addEventListener('click', function(){axios.get('/toggle').then(function(response){console.log('toggle');});});</script></html>";
    client.println(htmlCode);
  }
  // Return the response 
  delay(1);
 
} 
