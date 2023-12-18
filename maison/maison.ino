#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>                           // Esp8266/NodeMCU Library
#include <PubSubClient.h>                             // MQTT Library
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define anaPhoto A0
#define ventillo 14
#define ampoule 12
int temoinL=0;
int temoinV=0;
SoftwareSerial NodeMCU(D2,D3);

//information de connnexion au serveur mqtt
const char* mqtt_server = "192.168.1.167";       // MQTT Server IP Address
const char* user = "eliot";
const char* password = "eliot";
const char* clientID = "noeud1";     // The client id identifies the NodeMCU device.
const char* topicT = "maison";  // Topic temperature
const char* willTopic = "maison";    // Topic Status
const char* willMessage = "0";              // 0 - Disconnecetd
int counter = 0;                            // Used to reconnect to MQTT server
int willQoS = 0;
const char* willRetain = "connecté";
//Buffer pour encodage des messages recus
char message_buff[100];

const char* topicNotify = "notify";

//variable pour la connexion wifi
const char* ssid = "YET";
const char* passwifi = "yeteliot@12";


//fonction de connexion wifi
void setup_wifi() {
  // connexion au reseau wifi
  Serial.println();
  Serial.print("connexion à ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwifi);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); 

//fànction

void reconnect(){            
    while (!client.connected()) {
        Serial.print("Attente de connexion MQTT...");
        if (client.connect(clientID,user,password, willTopic, willQoS, willRetain, willMessage, true)) { 
            client.publish(willTopic, "1", true);  
            Serial.println("Connected to MQTT Broker!");
            counter = 0;
        } 
        else {
            Serial.println("Connection to MQTT Broker failed. Trying again in 2 seconds");
            ++counter;
            if (counter > 180) ESP.reset();
            delay(2000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {

  int i = 0;
  Serial.println("Message recu =>  topic: " + String(topic));
  
    //Serial.print(" | longueur: " + String(length,DEC));
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
  
	NodeMCU.print(msgString);
	NodeMCU.println("\n");
	delay(30);
  Serial.print(msgString);
  Serial.print("\n");
  if (msgString[0]=='c')
  {
    Serial.print("chauffage regle a:");
      Serial.println(msgString);
      //client.publish(topicNotify, "chauffage activee");
  }

 int x = msgString.toInt();
  switch (x){
    case 1:
      digitalWrite(ampoule,HIGH);
      //client.publish(topicNotify, "commande-lumiere_)N");
      temoinL=1;
      break;
    case 2:
      digitalWrite(ampoule,LOW);
      //client.publish(topicNotify, "lumiere off");
      temoinL=0;
      break;
    case 3:
      digitalWrite(ventillo,HIGH);
      //client.publish(topicNotify, "ventillo activee");
      temoinV=1;
      break;
    case 4:
      digitalWrite(ventillo,LOW);
      //client.publish(topicNotify, "ventillo off");
      temoinV=0;
      break;
      
  }

}

//Fonction pour publier un float sur un topic
void mqtt_publish(String topic, float t){
  char top[topic.length()+1];
  topic.toCharArray(top,topic.length()+1);
  char t_char[50];
  String t_str = String(t);
  t_str.toCharArray(t_char, t_str.length() + 1);
  client.publish(top,t_char);
}


void setup() {
  Serial.begin(9600);
  delay(10);

  setup_wifi();
  if (client.connect(clientID,user,password, willTopic, willQoS, willRetain, willMessage, true)) {  // Connecting to MQTT Broker
    Serial.print(clientID);
      Serial.println(" connected to MQTT Broker!");
  }
  else {
      Serial.print(clientID);
      Serial.println(" connection to MQTT Broker failed...");
  }
  //client.publish(willTopic, "1", true);
  client.subscribe("maison");
  //client.subscribe("lumiere");
  //client.subscribe("ventillo");
  //client.subscribe("portail");
  client.setCallback(callback);
  pinMode(anaPhoto,INPUT);
  pinMode(ventillo,OUTPUT);
  pinMode(ampoule,OUTPUT);
  dht.begin();
}

void loop() {
int valPir =1;
// put your main code here, to run repeatedly:
if (!client.connected()) { // Reconnecting to MQTT server if connection is lost
    reconnect();
}
client.loop();

delay(1000);

float t = dht.readTemperature();
Serial.print(t);
Serial.print("\n");
mqtt_publish("maison", t);
if(temoinV==0)
{
if (t>=25){
 digitalWrite(ventillo,HIGH);
 //client.publish(topicNotify,"ventillation declenchee");
 temoinV=0;
}
else{
  digitalWrite(ventillo,LOW);
  //client.publish(topicNotify,"ventillation arretee");
  temoinV=0;
}
}
else{
  //digitalWrite(ventillo,LOW);
  //client.publish(topicNotify,"ventillation arretee");
  temoinV=1;
}

delay(1000);

int valphoto = analogRead(anaPhoto);
Serial.print("luminosite : ");
Serial.print(valphoto);
Serial.print("\n");
if(temoinL==0)
{
  if(valphoto <=2){
    //client.publish(topicNotify, "presence dans l'obscurite");
    digitalWrite(ampoule,HIGH);
    temoinL=0;
  }
  else{
    temoinL=0;
    //client.publish(topicNotify, "la luminosité est bonne");
    digitalWrite(ampoule,LOW);
  }    
}
else{
    //client.publish(topicNotify, "La commande a distance");
    //digitalWrite(ampoule,HIGH);
    temoinL=1;
  } 

delay(1000);
}
