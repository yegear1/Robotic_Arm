#include <WiFi.h>
#include <WifiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

//Importando os outros arquivos
#include <servoController.h>
#include <indexHTML.h>

#define LED_BUILTIN 2

const char* host = "esp32"; // é usado com o mDNS
const char* ssid = "Odim"; 
const char* password = "mrosa123"; 

// Inicializa o servidor Web
WebServer server(80);

// Cria as estrutura das rotas
struct Route {
  const char* path;
  Function *response;
};

// Define as rotas e ações para cada botão
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

  // Conecta ao Wifi
  while (WiFi.status() != WL_CONNECTED) { 
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
  };

  // Define o endereço da hospedagem para http://esp32.local,
  // se falhar ele pisca o LED 5 vezes
  if (!MDNS.begin(host)) {
    for(int count = 0; count <= 5; count++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
    };
  };

  // Rota para tratar as requisições de acesso, puxando o index
  server.on("/", HTTP_GET, [](){ // http://esp32.local
    server.send(200, "text/html", indexHTML);
  });

  // Rota para parar o movimento dos servos
  server.on("/button=0", HTTP_GET, []() {
    digitalWrite(LED_BUILTIN, LOW);

    move = standStill;

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  const int routeCount = sizeof(routes) / sizeof(Route);

  // Percorre todo o array Routes, configurando cada rota
  // definindo uma função de respota a ela
  for (int i = 0; i < routeCount; i++) {

    server.on(routes[i].path, HTTP_GET, [&routes, i]() {
      digitalWrite(LED_BUILTIN, HIGH);

      move = routes[i].response;

      server.sendHeader("Connection", "close");
      server.send(204);
    });
  }

  // Caso não encontre uma rota conhecida
  server.onNotFound([](){
    digitalWrite(LED_BUILTIN, LOW);

    server.sendHeader("Connection", "close");
    server.send(204);
  });

  server.begin();

} 

void loop(void) {
  server.handleClient(); // Processa as requisições

  move(); // Executa os movimentos

  delay(cycle); // Adiciona um atraso nas execuções

} 
