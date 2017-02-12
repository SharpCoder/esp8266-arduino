#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

class HttpMessage {
  char* method;
  char* ipAddr;
  char* resource;
  char* host;
  char* headers[15];
  char* port;
  int headerCount;
  
  public:
    HttpMessage(char* ipAddr, char* port, char* resource);
    void setMethod(char* method);
    void setResource(char* resource);
    void setHost(char* host);
    void addHeader(char* header);
    char* getIpAddr();
    char* getPort();
    char* toString();
    int getMessageLength();
    char* getHeaderString();
};

#endif
