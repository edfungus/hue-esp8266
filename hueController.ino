#include <ESP8266WiFi.h>
#include "Encoder.h"
#include "Button.h"
#include "Secret.h"

#define STEP 1
#define HUE_HOST "192.168.1.1"
#define onOffButtonPin 14

Secret secret;
Encoder briEncoder(5, 4, STEP);
Button onOffButton(onOffButtonPin);
WiFiClient client;

void setup() {
    Serial.begin(115200);
    setupWifi();
    setupEncoders();
}

void loop() {
    if(briEncoder.getMovement() != 0){
        int mv = briEncoder.getMovement() * 10;
        adjustHueBri(mv);
        briEncoder.clearMovement();
    }
    int state = onOffButton.check();
    if (state == 1) {
        onHue("true");
    }
    if (state == 2) {
        onHue("false");
    }
}

void briInterrupt(){
    briEncoder.interrupt();
}

void setupWifi() {
    WiFi.begin(secret.getWifiSSID(), secret.getWifiPassword()); 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Waiting to connect…");
    }
    Serial.print("Connect with IP address: ");
    Serial.println(WiFi.localIP());
}

void setupEncoders() {
    Serial.println("Setting up encoders");
    briEncoder.setupPins(briInterrupt);
}

void adjustHueBri(int increment){
    String postData = "{\"bri_inc\":"+String(increment)+"}";
    sendToHue(postData);
}

void onHue(String state){
    String postData = "{\"on\":"+state+"}";
    sendToHue(postData);
}

void sendToHue(String postData) {
    while (!client.connect(HUE_HOST, 80)) {
        Serial.println("Connecting to hue ... ");
    }

    client.println("PUT /api/"+String(secret.getHueUsername())+"/groups/1/action HTTP/1.1");
    client.println("Host: " + String(HUE_HOST));
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);

    // while(client.available()){
    //     String line = client.readStringUntil('\r');
    //     Serial.print(line);
    // }
}