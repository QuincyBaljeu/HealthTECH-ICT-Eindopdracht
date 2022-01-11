#include <ESP8266WiFi.h> 
#include <PubSubClient.h>

const char* ssid = "Hotspot";
const char* password = "macaroni12";

const char* mqttUserId = "TestID";

const char* mqttServer = "broker.hivemq.com";

void setupWifi(char*, char*);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void reconnect() {

  while(!mqttClient.connected()){
    Serial.println("Connection to MQTT server");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqttClient.publish("outTopic", "hello world");
      // ... and resubscribe
      mqttClient.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(topic);
  Serial.print(": ");

  for(int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.print("\n");
}

void setupWifi(char* ssid, char* password){
  
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
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupWifi("Hotspot", "macaroni12");
  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(callback);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    mqttClient.publish("QuincyTestASD", msg);
  }
}
