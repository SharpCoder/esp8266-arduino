#include "Arduino.h"
#include "httpMessage.h"
#include "stringUtils.h"

HttpMessage::HttpMessage(char* ipAddr, char* port, char* resource) {
  this->ipAddr = ipAddr;
  this->resource = resource;
  this->headerCount = 0;
  this->port = port;
}

char* HttpMessage::getPort() {
  return this->port;
}

void HttpMessage::setMethod(char* method) {
  this->method = method;
}

void HttpMessage::setResource(char* resource) {
  this->resource = resource;
}

void HttpMessage::setHost(char* host) {
  this->host = host;
}

void HttpMessage::addHeader(char* header) {
  int headerSize = strlen(header);
  this->headers[this->headerCount] = allocStr(headerSize);
  strcpy(this->headers[this->headerCount], header);
  this->headers[this->headerCount][headerSize] = '\n';
  this->headerCount++;
}

char* HttpMessage::getHeaderString() {
  return cat(this->headers, this->headerCount);
}

char* HttpMessage::getIpAddr() {
  return this->ipAddr;
}

char* HttpMessage::toString() {
  char* components[] = {
    this->method,
    " ",
    this->resource,
    " HTTP/1.1\n",
    "host: ",
    this->host,
    "\n",
    this->getHeaderString(),
    "\n\n"
  };
  
  return cat(components, 9);
}

int HttpMessage::getMessageLength() {
  return strlen(this->toString());
}
