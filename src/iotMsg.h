#ifndef IOT_MSG_H
#define IOT_MSG_H

#include "Arduino.h"

class IotMsg {

  public:
    IotMsg();
    void setDeliver(bool shouldDeliver);
    char* toJSON();

  private:
    char uptime[10];
    bool deliver;

};

#endif
