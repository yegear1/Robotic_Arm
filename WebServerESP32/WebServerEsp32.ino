#include <WiFi.h>
#include <WifiClient.h>
#include <WebServer.h>
#include <ESPmDNS>

#define LED_BUILTIN 2

const char* host = "esp32";
const char* ssid = "ELDRADO"; 
const char* password = "amazon123"; 

WebServer server(80);

struct Route {
  const char* path;
  Function *response;
}

Route routes[] = {
 {"/button=key_8", closedClaw},
 {"/button=key_7", openClaw},
 {"/button=key_i", raiseArm},
 {"/button=key_k", lowerArm},
 {"/button=key_w", strechArm},
 {"/button=key_s", retractArm},
 {"/button=key_a", rotateLeft},
 {"/button=key_d", rotateRight},
 {"/button=key_5", moveUp},
 {"/button=key_6", moveBack},
 {"/button=key_1", performAutomaticMoviment},
 {"/button=key_2", recordMoviment},
 {"/button=key_3", deleteMoviment},
}

void setup(void) { 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Wifi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (!MDNS.begin(host)) { //http://esp32.local
    for(int count = 0; count <= 5; count++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", "<h1>Código HTML</h1>");
  });

  server.on("/button=0", HTTP_GET [](){
    digitalWrite(LED_BUILTIN, LOW);

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  const int routeCount = sizeof(routes) / sizeof(Route);

  server.on("/button=key_1", HTTP_GET [](){
    digitalWrite(LED_BUILTIN, HIGH);

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  server.on("/button=key_2", HTTP_GET [](){
    digitalWrite(LED_BUILTIN, HIGH);

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  server.on("/button=key_3", HTTP_GET [](){
    digitalWrite(LED_BUILTIN, HIGH);

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  server.onNotFound([](){
    digitalWrite(LED_BUILTIN, LOW);

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  server.begin();

} 

void loop() {


} 
