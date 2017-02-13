#include "Arduino.h"
#include "httpMessage.h"
#include "stringUtils.h"

HttpMessage::HttpMessage(const char* ipAddr, const char* port, const char* resource) {
  this->ipAddr = ipAddr;
  this->resource = resource;
  this->port = port;
  this->resetMemory();
}

void HttpMessage::resetMemory() {
  this->body = NULL;
  this->buffer = NULL;
  this->headerCount = 0;
  this->pos = 0;
}

char* HttpMessage::getPort() {
  return this->port;
}

void HttpMessage::setMethod(char* method) {
  this->method = method;
}

void HttpMessage::setHost(char* host) {
  this->host = host;
}

void HttpMessage::setBody(char* body) {
  this->body = cpystr(body);
}


char* HttpMessage::getBody() {
  return this->body;
}

char* HttpMessage::getBodyString() {
  if (this->body == NULL) {
    return "";
  } else {
    int size = strlen(this->body);
    char* bodyComponents[] = {"Content-Length: ", atoi(size), "\n\n", this->body};
    return cat(bodyComponents, 4);
  }
}

void HttpMessage::addHeader(char* header) {
  if (this->pos == 0) {
    this->buffer = allocStr(128);
  }
  
  char* ptr = (char*)((char*)this->buffer + this->pos);
  int size = strlen(header);
  for(int i= 0; i < size + 1; i++) {
    if (i == size) {
      *((char*)ptr + i) = '\n';
    } else {
      *((char*)ptr + i) = *((char*)header + i);
    }
  }
  this->pos += size + 1;
}

char* HttpMessage::getHeaderString() {
  char* header = allocStr(this->pos);
  for(int i = 0; i < this->pos; i++) {
    *((char*)header + i) = *((char*)this->buffer + i);
  }
  return header;
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
    this->getBodyString()
  };

  return cat(components, 9);
}

int HttpMessage::getMessageLength() {
  return strlen(this->toString());
}
