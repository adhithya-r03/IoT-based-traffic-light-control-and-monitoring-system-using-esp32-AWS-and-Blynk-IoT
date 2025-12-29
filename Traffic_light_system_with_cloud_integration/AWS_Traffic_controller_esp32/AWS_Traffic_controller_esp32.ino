#define AWS_IOT_PUBLISH_TOPIC   "******" //replace your publish topic
#define AWS_IOT_SUBSCRIBE_TOPIC "******" //replace your subscribe topic
#include <Arduino_BuiltIn.h>

#include <PubSubClient.h>

//#include <WiFi.h>
#include <WiFiClient.h>
//#include <BlynkSimpleEsp32.h>
#include <Arduino_BuiltIn.h>

#include "certs.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"



WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

int red1 = 26;
int green1 = 33;
int yellow1 = 25;
int red2 = 19;
int green2 = 5;
int yellow2 = 18;
int red3 = 32;
int green3 = 21;
int yellow3 = 3;
int red4 = 17;
int green4 = 15;
int yellow4 = 16;

const int pingPin1 = 13; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = 12; // Echo Pin of Ultrasonic Sensor
const int pingPin2 = 27; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = 14; // Echo Pin of Ultrasonic Sensor
const int pingPin3 = 22; // Trigger Pin of Ultrasonic Sensor
const int echoPin3 = 23; // Echo Pin of Ultrasonic Sensor
const int pingPin4 = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin4 = 4; // Echo Pin of Ultrasonic Sensor
bool trafficDetected1 = false;
bool trafficDetected2 = false;
bool trafficDetected3 = false;
bool trafficDetected4 = false;
bool executed1 = false;
bool executed2 = false;
bool executed3 = false;
bool executed4 = false;
unsigned long lastChangeTime = 0;
unsigned long greenDuration = 10000; // 10 seconds
int sig1 = 0;
int sig2 = 0;
int sig3 = 0;
int sig4 = 0;
int s1;
int s2;
int s3;
int s4;

void messageHandler(char* topic, byte* payload, unsigned int length) {
  Serial.print("incoming: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);
}


void connectAWS() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["signal1"] = s1;
  doc["signal2"] = s2;
  doc["signal3"] = s3;
  doc["signal4"] = s4;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void setup() {
  Serial.begin(115200);
  connectAWS();
  //Blynk.begin(auth, ssid, pass);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(red3, OUTPUT);
  pinMode(red4, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(yellow4, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(green4, OUTPUT);
}

void loop() {
  //Blynk.run();
  
  unsigned long currentTime = millis();
  if (green1 == HIGH) {
    executed1 = true;
  }
  if (green2 == HIGH) {
    executed2 = true;
  }
  if (green3 == HIGH) {
    executed3 = true;
  }
  if (green4 == HIGH) {
    executed4 = true;
  }
  if (!trafficDetected1) {
    executed1 = false;
  }
  if (!trafficDetected2) {
    executed2 = false;
  }
  if (!trafficDetected3) {
    executed3 = false;
  }
  if (!trafficDetected4) {
    executed4 = false;
  }
  if( trafficDetected1==true || trafficDetected2==true || trafficDetected3==true || trafficDetected4==true ){
    lastChangeTime = currentTime;
    publishMessage();
    
  }
  

  int distance1 = calculatedistance(pingPin1, echoPin1);
  int distance2 = calculatedistance(pingPin2, echoPin2);
  int distance3 = calculatedistance(pingPin3, echoPin3);
  int distance4 = calculatedistance(pingPin4, echoPin4);

  if (distance1 < 10) {
    trafficDetected1 = true;
    trafficDetected2 = false;
    trafficDetected3 = false;
    trafficDetected4 = false;
    s1 = sig1++;
    
  } else if (distance2 < 10) {
    trafficDetected1 = false;
    trafficDetected2 = true;
    trafficDetected3 = false;
    trafficDetected4 = false;
    s2 = sig2++;
    
  } else if (distance3 < 10) {
    trafficDetected1 = false;
    trafficDetected2 = false;
    trafficDetected3 = true;
    trafficDetected4 = false;
    s3 = sig3++;
    
  } else if (distance4 < 10) {
    trafficDetected1 = false;
    trafficDetected2 = false;
    trafficDetected3 = false;
    trafficDetected4 = true;
    s4 = sig4++;
    
  } else {
    trafficDetected1 = false;
    trafficDetected2 = false;
    trafficDetected3 = false;
    trafficDetected4 = false;
  }

  //unsigned long currentTime = millis();
    if (trafficDetected1 && digitalRead(green1) == LOW) {
      
      digitalWrite(red1, LOW);
      

      
    
      if(digitalRead (green2)== HIGH){
        digitalWrite(red4,HIGH);
        digitalWrite(red3,HIGH);
	      digitalWrite(green2, LOW);
	      digitalWrite(yellow2,HIGH);
        digitalWrite(yellow1,HIGH);
	      delay(1000);
	      digitalWrite(yellow2,LOW);
        digitalWrite(yellow1,LOW);
	      digitalWrite(red2,HIGH);
      }
      else if(digitalRead (green3)== HIGH){
        digitalWrite(red2,HIGH);
        digitalWrite(red4,HIGH);
	      digitalWrite(green3, LOW);
	      digitalWrite(yellow3,HIGH);
        digitalWrite(yellow1,HIGH);
	      delay(1000);
	      digitalWrite(yellow3,LOW);
        digitalWrite(yellow1,LOW);
	      digitalWrite(red3,HIGH);
      }
      else if(digitalRead (green4)== HIGH){
        digitalWrite(red2,HIGH);
        digitalWrite(red3,HIGH);
	      digitalWrite(green4, LOW);
	      digitalWrite(yellow4,HIGH);
        digitalWrite(yellow1,HIGH);
	      delay(1000);
	      digitalWrite(yellow4,LOW);
        digitalWrite(yellow1,LOW);
	      digitalWrite(red4,HIGH);
      }

      digitalWrite(green1, HIGH);
    } 
    else if (trafficDetected2 && digitalRead(green2) == LOW) {
      
      
      digitalWrite(red2, LOW);
      
    
      
      if(digitalRead (green1)== HIGH){
        digitalWrite(red4,HIGH);
        digitalWrite(red3,HIGH);
	      digitalWrite(green1, LOW);
	      digitalWrite(yellow1,HIGH);
        digitalWrite(yellow2,HIGH);
	      delay(1000);
	      digitalWrite(yellow1,LOW);
        digitalWrite(yellow2,LOW);
	      digitalWrite(red1,HIGH);
      }
      else if(digitalRead (green3)== HIGH){
        digitalWrite(red1,HIGH);
        digitalWrite(red4,HIGH);
	      digitalWrite(green3, LOW);
	      digitalWrite(yellow3,HIGH);
        digitalWrite(yellow2,HIGH);
	      delay(1000);
	      digitalWrite(yellow3,LOW);
        digitalWrite(yellow2,LOW);
	      digitalWrite(red3,HIGH);
      }
      else if(digitalRead (green4)== HIGH){
        digitalWrite(red1,HIGH);
        digitalWrite(red3,HIGH);
	      digitalWrite(green4, LOW);
	      digitalWrite(yellow4,HIGH);
        digitalWrite(yellow2,HIGH);
	      delay(1000);
	      digitalWrite(yellow4,LOW);
        digitalWrite(yellow2,LOW);
	      digitalWrite(red4,HIGH);
      }
    
      digitalWrite(green2, HIGH);
    } 
    else if (trafficDetected3 && digitalRead(green3) == LOW) {
      
      
      digitalWrite(red3, LOW);
      
    
      
      if(digitalRead (green2)== HIGH){
        digitalWrite(red1,HIGH);
        digitalWrite(red4,HIGH);
	      digitalWrite(green2, LOW);
	      digitalWrite(yellow2,HIGH);
        digitalWrite(yellow3,HIGH);
	      delay(1000);
	      digitalWrite(yellow2,LOW);
        digitalWrite(yellow3,LOW);
	      digitalWrite(red2,HIGH);
      }
      else if(digitalRead (green1)== HIGH){
        digitalWrite(red2,HIGH);
        digitalWrite(red4,HIGH);
	      digitalWrite(green1, LOW);
	      digitalWrite(yellow1,HIGH);
        digitalWrite(yellow3,HIGH);
	      delay(1000);
	      digitalWrite(yellow1,LOW);
        digitalWrite(yellow3,LOW);
	      digitalWrite(red1,HIGH);
      }
      else if(digitalRead (green4)== HIGH){
        digitalWrite(red1,HIGH);
        digitalWrite(red2,HIGH);
	      digitalWrite(green4, LOW);
	      digitalWrite(yellow4,HIGH);
        digitalWrite(yellow3,HIGH);
	      delay(1000);
	      digitalWrite(yellow4,LOW);
        digitalWrite(yellow3,LOW);
	      digitalWrite(red4,HIGH);
      }
    
      digitalWrite(green3, HIGH);
    } 
    else if(trafficDetected4 && digitalRead(green4) == LOW){
      
      digitalWrite(red4, LOW);
      
      
    
      
      if(digitalRead (green2)== HIGH){
        digitalWrite(red1,HIGH);
        digitalWrite(red3,HIGH);
	      digitalWrite(green2, LOW);
	      digitalWrite(yellow2,HIGH);
        digitalWrite(yellow4,HIGH);
	      delay(1000);
	      digitalWrite(yellow2,LOW);
        digitalWrite(yellow4,LOW);
	      digitalWrite(red2,HIGH);
      }
      else if(digitalRead (green3)== HIGH){
        digitalWrite(red1,HIGH);
        digitalWrite(red2,HIGH);
	      digitalWrite(green3, LOW);
	      digitalWrite(yellow3,HIGH);
        digitalWrite(yellow4,HIGH);
	      delay(1000);
	      digitalWrite(yellow3,LOW);
        digitalWrite(yellow4,LOW);
	      digitalWrite(red3,HIGH);
      }
      else if(digitalRead (green1)== HIGH){
        digitalWrite(red2,HIGH);
        digitalWrite(red3,HIGH);
	      digitalWrite(green1, LOW);
	      digitalWrite(yellow1,HIGH);
        digitalWrite(yellow4,HIGH);
	      delay(1000);
	      digitalWrite(yellow1,LOW);
        digitalWrite(yellow4,LOW);
	      digitalWrite(red1,HIGH);
      }
    
      digitalWrite(green4, HIGH);
    }
    else {
      executed1 = true;
      executed2 = true;
      executed3 = true;
      
      if (currentTime - lastChangeTime >= greenDuration) {
        lastChangeTime = currentTime;
        if (digitalRead(green1) == HIGH) {
          digitalWrite(green1, LOW);

        

          digitalWrite(red2, LOW);
          digitalWrite(yellow1, HIGH);
          digitalWrite(yellow2, HIGH);
          delay(1000);
          digitalWrite(yellow1, LOW);
          digitalWrite(yellow2, LOW);
          digitalWrite(red1, HIGH);
          digitalWrite(green2, HIGH);
        } 
        else if (digitalRead(green2) == HIGH) {
          digitalWrite(green2, LOW);

        

          digitalWrite(red3, LOW);
          digitalWrite(yellow3, HIGH);
          digitalWrite(yellow2, HIGH);
          delay(1000);
          digitalWrite(yellow2, LOW);
          digitalWrite(yellow3, LOW);
          digitalWrite(red2, HIGH);
          digitalWrite(green3, HIGH);
        } 
        else if (digitalRead(green3) == HIGH) {
          digitalWrite(green3, LOW);

        

          digitalWrite(red4, LOW);
          digitalWrite(yellow3, HIGH);
          digitalWrite(yellow4, HIGH);
          delay(1000);
          digitalWrite(yellow3, LOW);
          digitalWrite(yellow4, LOW);
          digitalWrite(red3, HIGH);
          digitalWrite(green4, HIGH);
        } 
        else if(digitalRead(green4) == HIGH){
          digitalWrite(green4, LOW);

        

          digitalWrite(red1, LOW);
          digitalWrite(yellow1, HIGH);
          digitalWrite(yellow4, HIGH);
          delay(1000);
          digitalWrite(yellow1, LOW);
          digitalWrite(yellow4, LOW);
          digitalWrite(red4, HIGH);
          digitalWrite(green1, HIGH);

        }
        else {
          digitalWrite(red1, LOW);
          digitalWrite(yellow1, HIGH);
          delay(1000);
          digitalWrite(yellow1, LOW);
          digitalWrite(green1, HIGH);
        }
      }
    }
  //Blynk.virtualWrite(V0, s1); 
  //Blynk.virtualWrite(V1, s2); 
  //Blynk.virtualWrite(V2, s3);
  //Blynk.virtualWrite(V3, s4);
  
  
  
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

int calculatedistance(int pingPin, int echoPin) {
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

void yellow1glow(){
  digitalWrite(yellow1,HIGH);
  delay(2000);
  digitalWrite(yellow1,LOW);
}

void yellow2glow(){
  digitalWrite(yellow2,HIGH);
  delay(2000);
  digitalWrite(yellow2,LOW);
}

void yellow3glow(){
  digitalWrite(yellow3,HIGH);
  delay(2000);
  digitalWrite(yellow3,LOW);
}
void yellow4glow(){
  digitalWrite(yellow4,HIGH);
  delay(2000);
  digitalWrite(yellow4,LOW);
}


