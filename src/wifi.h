#ifndef PIMEI_WIFI_H
#define PIMEI_WIFI_H

#include "Arduino.h"
#include "httpMessage.h"

class Wifi {
  public:
    Wifi();
    void connect(char* ssid, char* pwd);
    void getStatus();
    void disconnect();
    void reset();
    void get(HttpMessage* message);
    bool isConnected();
  private:
    int errors = 0;
    bool connected;
    void blink(int count);
    bool sendUntil(char* command, char* target);
};

#endif
