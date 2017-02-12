#include "Arduino.h"
#include "wifi.h"
#include "stringUtils.h"

Wifi::Wifi() {
  Serial.begin(115200);
  Serial.setTimeout(5000);
  pinMode(13, OUTPUT);
}

void Wifi::connect(char* ssid, char* pwd) {
  char* args[] = { "AT+CWJAP=", "\"", ssid, "\",\"", pwd, "\"" };
  if (this->sendUntil(cat(args, 6), "WIFI GOT IP")) {
    this->connected = true;
  }
  this->blink(3);
}

bool Wifi::isConnected() {
  return this->connected;
}

void Wifi::getStatus() {
  this->sendUntil("AT", "OK");
}
    
void Wifi::disconnect() {
  this->sendUntil("AT+CWQAP", "OK");
  this->errors = 0;
  this->connected = false;
}

void Wifi::reset() {
  this->sendUntil("AT+RST", "OK");
}
    
void Wifi::get(HttpMessage* message) {
  char* request = message->toString();
  char* strSize = new char [15];
  sprintf(strSize, "%d", strlen(request) - 1);
  char* startArgs[] = {"AT+CIPSTART=\"TCP\",", "\"", message->getIpAddr(), "\",", message->getPort() };
  char* sendArgs[] = {"AT+CIPSEND=", strSize};

  this->sendUntil(cat(startArgs, 5), "OK");
  this->sendUntil("AT+CIPMODE=0\0", "OK");
  this->sendUntil(cat(sendArgs, 2), "OK");
  this->sendUntil(request, "OK");
  this->sendUntil("AT+CIPCLOSE", "OK");
}

bool Wifi::sendUntil(char* command, char* target) {
  char buffer[1024];
  for (int i = 0; i < 1024; i++) {
    buffer[i] = ' ';
  }
  
  int index = 0, timeout = 125;
  Serial.println(command);
  Serial.flush();

  while(timeout-- > 0) {
    delay(50);
    while(Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\r') {
        // End of line 
        buffer[index] = '\0';
        index = 0;
        char* temp = allocStr(index);
        strcpy(temp, buffer);
        if (strstr(temp, target) > 0) {
          // Consume the rest of the stream.
          return true;
        }
      } else {
        buffer[index++] = c;
      }
    }
  }

  if (this->errors++ >= 5) {
    this->disconnect();
  }
  Serial.println("Error Condition has been met");
  return false;
}

// *************
// Simple way to communicate over pin13
// with blinks.
// *************
void Wifi::blink(int count) {
  if (count <= 0) return;
  for(; count > 0; count--) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}

