#include <Arduino.h>
#include <WiFi.h>
#include <ThingSpeak.h>
 
#define WIFI_NETWORK "EACCESS" 
#define WIFI_PASSWORD "hostelnet" 
#define WIFI_TIMEOUT_MS 20000
#define CHANNEL_ID 2272635
#define CHANNEL_API_KEY "DMSAMBEL9S9PSYXE"

WiFiClient client;

const int ldr = 34;
int sensorValue = 0;
int led_graph = 0;


void connectToWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin (WIFI_NETWORK, WIFI_PASSWORD);
  unsigned long startAttemptTime = millis () ;
  while(WiFi.status() != WL_CONNECTED && millis () - startAttemptTime < WIFI_TIMEOUT_MS) {
    Serial.print(".");
    delay (100);
  }  
  if(WiFi.status() != WL_CONNECTED){
    Serial.println(" Failed!");
  }else{
    Serial.print("Connected!");
    Serial.println(WiFi. localIP());
  }
}   
void setup() {
  Serial.begin (115200);
  connectToWiFi();
  ThingSpeak.begin(client);
  pinMode(4, OUTPUT);
}
void loop(){
  
  int counter = 0;
  String Led_status = "";
  counter++;
  ThingSpeak.setField(1,counter);
  ThingSpeak.setField(3,sensorValue);

  sensorValue = analogRead(ldr);
  Serial.println(sensorValue);
  if(sensorValue<50){
    digitalWrite(4, HIGH);
    Led_status = "LED is ON";
    led_graph = 1 ;
    
    
  }
  else{
    digitalWrite(4, LOW);
    Led_status = "LED is OFF";
    led_graph = 0 ;
  }
  Serial.println(Led_status);
  ThingSpeak.setField(2,led_graph);


  ThingSpeak.writeFields(CHANNEL_ID,CHANNEL_API_KEY);
  delay(400);

}