#include <ESP8266WiFi.h> 
#include <PubSubClient.h>

const char* ssid = "Hotspot";
const char* password = "macaroni12";

const char* mqttUserId = "TestID";

const char* mqttServer = "broker.hivemq.com";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(50);

  Serial.println("Connecting to: ");
  Serial.print(ssid);
  
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to: ");
  Serial.print(ssid);

  Serial.println("IP address: ");
  Serial.print(WiFi.localIP());

  Serial.println("Connecting to: ");
  Serial.print(mqttServer);
  
  if(mqttClient.connect(mqttUserId)){
    Serial.println("Connected to MQTT");
  } else {
    Serial.println("Not connected to mqtt");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  mqttClient.loop();
}
