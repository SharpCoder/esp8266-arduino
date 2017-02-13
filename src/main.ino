
#include "wifi.h"
#include "stringUtils.h"
#include "iotMsg.h"
#include "httpMessage.h"

Wifi* wifi;
IotMsg* iotMsg;
HttpMessage* message;

const char* SSID = "NETWORK_NAME_HERE";
const char* PWD = "NETWORK_PASSWORD_HERE";

bool isConfigured = false;

void setup() {
  // put your setup code here, to run once:
  wifi = new Wifi();
  message = new HttpMessage();
  iotMsg = new IotMsg();
  
  // If you want the string buffers to work
  // this is necessary. I'll refactor it someday.
  initStringHelper();
  wifi->setHardwareResetPin(10);
  iotMsg->setDeliver(true);
}

void sendPing() {

  // Configure the things. This needs to be done
  // because we purge the stack each loop.
  message->resetMemory();  
  message->setMethod("GET");
  message->setHost("68.65.121.3");
  message->addHeader("Content-Type: application/json");
  
  wifi->initBuffer();
  wifi->getStatus();
  if (!wifi->reset()) {
    // If reset doesn't have an ip address then
    // we need to connect again.
   if (!wifi->connect(SSID, PWD)) {
      // If that failed, we're screwed this loop.
      delay(1000);
      return;
    } 
  }

  char* msg = iotMsg->toJSON();
  message->setBody(msg);
  wifi->send(message);
}


void loop() {
  // This is needed because I program like its
  // 2017, you know, as if memory isn't a problem... But I guess it is.
  resetStringHelper();
  sendPing();
  delay(30000);
  
}
