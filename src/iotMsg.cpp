#include "iotMsg.h"
#include "stringUtils.h"

IotMsg::IotMsg() {
}

void IotMsg::setDeliver(bool shouldDeliver) {
  this->deliver = shouldDeliver;
}

char* IotMsg::toJSON() {
  char* components[] = {
    "{",
    "\"state\":{",
    "\"reported\":{",
    "\"uptime\":",
    atoi(millis()),
    ",",
    "\"deliver\":",
    (this->deliver ? "true" : "false"), 
    "}}}"
  };
  return cat(components, 9);
}

