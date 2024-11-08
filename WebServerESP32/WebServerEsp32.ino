#include <WiFi.h>
#include <WifiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <servoController.h>
#include <indexHTML.h>

#define LED_BUILTIN 2

const char* host = "esp32";
const char* ssid = "Odim"; 
const char* password = "mrosa123"; 

WebServer server(80);

struct Route {
  const char* path;
  Function *response;
};

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
};

void setup(void) { 

  attachMotors();

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //Esperando conexão
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
  };

  if (!MDNS.begin(host)) { //http://esp32.local
    for(int count = 0; count <= 5; count++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    };
  };

  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", indexHTML);
  });

  server.on("/button=0", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, LOW);

    move = standStill;

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  const int routeCount = sizeof(routes) / sizeof(Route);

  for (int i = 0; i < routeCount; i++) {

    server.on(routes[i].path, HTTP_GET, [&routes, i]() {
      digitalWrite(LED_BUILTIN, HIGH);

      move = routes[i].response;

      server.sendHeader("Connection", "close");
      server.send(204);
    });
  }

  server.onNotFound([](){
    digitalWrite(LED_BUILTIN, LOW);

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  server.begin();

} 

void loop(void) {
  server.handleClient();

  move();

  delay(cycle); // Permite a CPU para trocar para outras tarefas

} 