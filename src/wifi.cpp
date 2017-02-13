#include "Arduino.h"
#include "wifi.h"
#include "stringUtils.h"

#define WIFI_SERIAL_BUFFER_LENGTH 256

Wifi::Wifi() {
  Serial.begin(115200);
  Serial.setTimeout(10000);
  pinMode(13, OUTPUT);
  this->initBuffer();
}

void Wifi::initBuffer() {
  this->buffer = allocStr(WIFI_SERIAL_BUFFER_LENGTH);
}

void Wifi::setHardwareResetPin(long pin) {
  this->hardwareResetPin = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(25);
  digitalWrite(pin, HIGH);
}

void Wifi::hardwareReset() {
  if (this->hardwareResetPin == -1) {
    return;
  }

  digitalWrite(this->hardwareResetPin, LOW);
  delay(50);
  digitalWrite(this->hardwareResetPin, HIGH);
  delay(50);
}

long Wifi::getErrors() {
  return this->errors;
}

bool Wifi::connect(char* ssid, char* pwd) {
  char* args[] = { "AT+CWJAP=", "\"", ssid, "\",\"", pwd, "\"" };
  if (this->sendUntil(cat(args, 6), "WIFI GOT IP")) {
    this->connected = true;
  } else {
    this->handleError();
    return false;
  }
  this->blink(3);
  return true;
}

bool Wifi::isConnected() {
  return this->connected;
}

void Wifi::getStatus() {
  this->sendUntil("AT", "OK");
}
    
void Wifi::disconnect() {
  this->errors = 0;
  this->connected = false;
  this->sendUntil("AT+CWQAP", "OK");
  this->hardwareReset();
}

bool Wifi::reset() {
  this->connected = false;
  if(this->sendUntil("AT+RST", "WIFI GOT IP")) {
    this->connected = true;
    return true;
  }
  return false;
}
    
void Wifi::send(HttpMessage* message) {
  char* request = message->toString();
  char* startArgs[] = {"AT+CIPSTART=\"TCP\",", "\"", message->getIpAddr(), "\",", message->getPort() };
  char* sendArgs[] = {"AT+CIPSEND=", atoi(strlen(request))};

  if (this->sendUntil(cat(startArgs, 5), "OK")) {
    if (this->sendUntil("AT+CIPMODE=0", "OK")) {
      if (this->sendUntil(cat(sendArgs, 2), "OK")) {
        if (this->sendUntil(request, "OK")) {
        }
      }
    }
  } else {
    this->handleError();
  }
  
  this->sendUntil("AT+CIPCLOSE", "OK");
}

void Wifi::handleError(void) {
  this->errors++;
  this->disconnect();
  Serial.println("Error condition has been met");
}

bool Wifi::sendUntil(char* command, char* target) {
  for (int i = 0; i < WIFI_SERIAL_BUFFER_LENGTH; i++) {
    *(this->buffer + i) = ' ';
  }
  
  int index = 0, timeout = 500;
  Serial.println(command);
  Serial.flush();
  
  while(timeout-- > 0) {
    unsigned long targetMillis = millis() + 500;

    // Safe(er) delay
    while(millis() <= targetMillis) {
      delay(5);
    }
    
    while(Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\r') {
        // End of line 
        *(this->buffer + index) = '\0';
        index = 0;
        if (strstr(buffer, target) > 0) {
          // Consume the rest of the stream.
          return true;
        } else {
          continue;
        }
      } else {
        *(this->buffer + index) = c;
      }
      if (++index > WIFI_SERIAL_BUFFER_LENGTH) {
        index = 0;
      }
    }
  }
  
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

