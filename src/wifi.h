#ifndef PIMEI_WIFI_H
#define PIMEI_WIFI_H

#include "Arduino.h"
#include "httpMessage.h"

class Wifi {
  public:
    Wifi();
    char* buffer;
    bool connect(char* ssid, char* pwd);
    void getStatus();
    void disconnect();
    bool reset();
    void send(HttpMessage* message);
    void setHardwareResetPin(long pin);
    void hardwareReset();
    long getErrors();
    bool isConnected();
    void initBuffer();
  private:
    long errors = 0;
    int hardwareResetPin = -1;
    bool connected;
    void blink(int count);
    bool sendUntil(char* command, char* target);
    void handleError();
};

#endif
