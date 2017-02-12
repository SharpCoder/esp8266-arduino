
#include "wifi.h"
#include "httpMessage.h"

Wifi* wifi;
const char* SSID = "NETWORK_NAME_HERE";
const char* PWD = "NETWORK_PASSWORD_HERE";

bool isConfigured = false;

void setup() {
  // put your setup code here, to run once:
  wifi = new Wifi();
}

void loop() {
  if (!isConfigured) {
    Serial.println("Starting the request");
    wifi->getStatus();
    
    if (!wifi->isConnected()) {
      wifi->reset();
      wifi->connect(SSID, PWD);
    }
    
    HttpMessage* message = new HttpMessage("68.65.121.3", "3000", "/");
    message->setMethod("GET");
    message->setHost("68.65.121.3");
    wifi->get(message);
    isConfigured = true;
    Serial.println("Finished");
  }
}
