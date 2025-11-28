#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ==========================================================
// 1. CONFIGURAÇÕES DE REDE E MQTT
// ==========================================================
const char* ssid = "SIMBA E THOR";
const char* password = "2499509301803ST"; 

const char* mqtt_server = "broker.hivemq.com"; 
const int mqtt_port = 1883;
const char* mqtt_topic = "MACK10420225/Temperatura"; 

// ==========================================================
// 2. CONFIGURAÇÃO DE HARDWARE (PINOS)
// ==========================================================
const int PIN_TEMP = 4;
const int PIN_PH = 34;
const int PIN_TURBIDEZ = 39;

// ==========================================================
// 3. VARIÁVEIS GLOBAIS E CLIENTES
// ==========================================================
// Configuração do sensor de temperatura
OneWire oneWire(PIN_TEMP);
DallasTemperature sensors(&oneWire);

// Configuração do MQTT e Wi-Fi
WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis para as leituras
float ph_value = 0.0;
float temp_celsius = 0.0;
float turb_raw = 0.0;


// ==========================================================
// FUNÇÃO DE RECONEXÃO MQTT
// ==========================================================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao HiveMQ...");
    String clientId = "ESP32-Agua-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

// ==========================================================
// SETUP
// ==========================================================
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nIniciando sistema de monitoramento de água...");

  // Inicializa o sensor de temperatura DS18B20
  sensors.begin();
  
  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!");

  // Configura o servidor MQTT
  client.setServer(mqtt_server, mqtt_port);
}

// ==========================================================
// LOOP PRINCIPAL
// ==========================================================
void loop() {
  // Mantém a conexão MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // --- 1. LEITURA DE TEMPERATURA (DS18B20) ---
  sensors.requestTemperatures();
  temp_celsius = sensors.getTempCByIndex(0);
  
  // --- 2. LEITURA DE pH ---
  int raw_ph = analogRead(PIN_PH);
  float voltage = raw_ph * (3.3 / 4095.0);
  // Conversão básica de pH (usando a fórmula do Código 1)
  ph_value = 7.0 - ((voltage - 2.5) / 0.18);

  // --- 3. LEITURA DE TURBIDEZ ---
  turb_raw = analogRead(PIN_TURBIDEZ);
  
  // --- 4. EXIBIÇÃO NO MONITOR SERIAL ---
  Serial.println("----------------------------------------");
  Serial.print("Temperatura: ");
  Serial.print(temp_celsius);
  Serial.println(" ºC");

  Serial.print("pH (Raw/Value): ");
  Serial.print(raw_ph);
  Serial.print(" | ");
  Serial.println(ph_value);

  Serial.print("Turbidez (Raw): ");
  Serial.println(turb_raw);
  
  // Lógica de estado da água do Código 1
  Serial.print("Estado da água: "); 
  if (turb_raw > 1500) { 
    Serial.println("LIMPA"); 
  } else if (turb_raw > 600) { 
    Serial.println("POUCO SUJA"); 
  } else { 
    Serial.println("SUJA"); 
  }


  // --- 5. CRIAÇÃO E ENVIO DO JSON PARA MQTT ---
  // Formato: {"temp":25.0, "ph":7.0, "turb":10.0}

  char jsonBuffer[128];
  snprintf(jsonBuffer, sizeof(jsonBuffer), 
    "{\"temp\": %.2f, \"ph\": %.2f, \"turb\": %.2f}", 
    temp_celsius, ph_value, turb_raw);

  Serial.print("Enviando MQTT: ");
  Serial.println(jsonBuffer);

  // Envia para o Broker
  client.publish(mqtt_topic, jsonBuffer);

  delay(5000);
}