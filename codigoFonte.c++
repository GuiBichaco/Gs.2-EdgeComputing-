#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Configurações da rede WIFI.
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";  // Substitua pela senha da sua rede WIFI

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "crotopus_gs2_mqtt";
const char *TOPIC_SUBSCRIBE_DISTANCE = "globalsolution2/iot/distance";


// Configurações de Hardware
#define PIN_DHT 12
#define RED_LED 4
#define YELLOW_LED 2
#define GREEN_LED 15
#define ECHO_PIN 21
#define TRIG_PIN 19
#define PUBLISH_DELAY 2000
const int buzzerPin = 18;

// Variáveis globais
WiFiClient espClient;
PubSubClient MQTT(espClient);
unsigned long publishUpdate = 0;
const int TAMANHO = 200;


// Protótipos de funções
void updateSensorValues();
void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT();
void reconnectWiFi();
void checkWiFIAndMQTT();


void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}



  //Verificação de distancia em modo automatica, aqui o valor para concluir a simulação é alterado sozinho via MQTT no node-red
void callbackMQTT(char *topic, byte *payload, unsigned int length) {
  // Converte o payload para uma string
  String msg = String((char*)payload).substring(0, length);

  Serial.printf("Mensagem recebida via MQTT: %s do tópico: %s\n", msg.c_str(), topic);
  //(para fins de depuração)
  //Serial.println("Callback MQTT acionado");

  // Verifica se o tópico é o correto
  if (strcmp(topic, TOPIC_SUBSCRIBE_DISTANCE) == 0) {
    // Converte a mensagem para um número
    int distance = msg.toInt();

    // Sorteia um valor entre 0 e 400
    int randomValue = random(401);

    // Exibe o valor sorteado no console (para fins de depuração)
    //Serial.printf("Valor sorteado: %d\n", randomValue);

    // Determina a situação do paciente com base no valor sorteado
    String status;
    if (randomValue <= 100) {
      status = "Grave";
    } else if (randomValue <= 200) {
      status = "Moderada";
    } else {
      status = "Controlada";
    }

    // Exibe a situação do paciente no console
    Serial.printf("Situação do paciente: %s\n", status.c_str());

    if (status == "Grave") {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);

      tone(buzzerPin, 1000); 
      delay(5000); 
      noTone(buzzerPin);  
      delay(1000);  
    } else if (status == "Moderada") {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);

      tone(buzzerPin, 1000); 
      delay(2000);  
      noTone(buzzerPin);
      delay(1000);  
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
    }
  }
}




void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando conectar com o Broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      MQTT.subscribe(TOPIC_SUBSCRIBE_DISTANCE);
    } else {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi(void) {
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wifi conectado com sucesso");
  Serial.print(SSID);
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  
  
  
  
  
  
  initWiFi();
  initMQTT();
  MQTT.subscribe(TOPIC_SUBSCRIBE_DISTANCE);

  // Inicializar o LEDC para o canal usado pelo buzzer
  ledcSetup(0, 1000, 8);  // Canal 0, frequência de 1000 Hz, resolução de 8 bits
  ledcAttachPin(buzzerPin, 0);
}

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}



void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();

  float distance = readDistanceCM();


  //Verificação de distancia em modo manual, aqui terá que alterar o valor no próprio sensor para concluir a simulação
  // if(distance <= 100){

  //   digitalWrite(RED_LED, HIGH);
  //   digitalWrite(YELLOW_LED, LOW);
  //   digitalWrite(GREEN_LED, LOW);
  //       // Tocar uma nota por 1 segundo
  //   tone(buzzerPin, 1000);  // Frequência de 1000 Hz
  //   delay(5000);  // Manter a nota por 1 segundo
  //   noTone(buzzerPin);  // Desligar o buzzer
  //   delay(1000);  // Aguardar 1 segundo antes de começar novamente
  //   Serial.print("Situação Grave - PROCURAR MÉDICO IMEDIATO EM NOSSO SISTEMA");
  // }else if (distance <= 200){
  //   digitalWrite(RED_LED, LOW);
  //   digitalWrite(GREEN_LED, LOW);
  //   digitalWrite(YELLOW_LED, HIGH);
  //     // Tocar uma nota por 1 segundo
  //   tone(buzzerPin, 1000);  // Frequência de 1000 Hz
  //   delay(2000);  // Manter a nota por 1 segundo
  //   noTone(buzzerPin);  // Desligar o buzzer
  //   delay(1000);  // Aguardar 1 segundo antes de começar novamente
  //   Serial.print("Situação Moderada - AGENDAR UMA CONSULTA O MAIS RÁPIDO POSSÍVEL");
  // }else{
  //   digitalWrite(RED_LED, LOW);
  //   digitalWrite(GREEN_LED, HIGH);
  //   digitalWrite(YELLOW_LED, LOW);
  //   Serial.print("Situação Controlada - AGENDAR UMA CONSULTA DE ROTINA, PACIENTE SEM RISCO");
  // }

  


  

  delay(2000);

  if ((millis() - publishUpdate) >= PUBLISH_DELAY) {
    publishUpdate = millis();
    float distance = readDistanceCM();

    if (!isnan(distance)) {
      StaticJsonDocument<TAMANHO> doc;
      doc["distance"] = distance;

      char buffer[TAMANHO];
      serializeJson(doc, buffer);
      MQTT.publish(TOPIC_SUBSCRIBE_DISTANCE, buffer);
      //Serial.println(buffer);
    }
  }

  
}
