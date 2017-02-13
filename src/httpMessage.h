#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

class HttpMessage {
  char* method;
  char* ipAddr;
  char* resource;
  char* host;
  char* port;
  char* body;
  char* buffer;
  long pos;
  int headerCount;
  
  public:
    HttpMessage(const char* ipAddr, const char* port, const char* resource);
    void setMethod(char* method);
    void setHost(char* host);
    void setBody(char* body);
    void addHeader(char* header);
    void resetMemory();
    char* getIpAddr();
    char* getPort();
    char* toString();
  private:
    char* bodyLength;
    int getMessageLength();
    char* getBody();
    char* getBodyString();
    char* getHeaderString();
    
};

#endif
