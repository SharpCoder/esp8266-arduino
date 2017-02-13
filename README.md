# esp8266-arduino
An arduino library for doing basic HTTP commands with the ESP8266 chip.

Currently, my library only supports /GET. However, that should change soon as I need
to actually make a POST request for my project. I wanted to get this open source library up
though, as an example for how to use the ESP8266 module with the arduino. Specifically wrt
making http requests. Which is probably what most people use it for.


The only (admittedly big) missing feature here is actually ip-address lookup.
You'll have to hard-code an ip address which you want to access.

**Pay little attention to the god awful string management library I wrote. It's there so you can dynamically adjust the message and do cool things with headers. But really, it's not going to work for long because it's a resource hog.**

## Supported protocols

* GET
* POST
* All of then, in theory

You can set the "method" on your request now.

## Using this library
You will need to go into the main.ino file, update the HttpMessage object and supply your own constants for **NETWORK_NAME_HERE** and **NETWORK_PASSWORD_HERE**.

I have added my own kind of Serial.readStringUntil()  method because the default one that arduino provides wasn't cutting it for me. It has some retry logic and seems to work pretty well for my purposes. You may find the *timeout* needs to be tweaked a bit. If you get a lot of "Error condition has been met" messages, that's probably why.

To support dynamic message bodies and headers and stuff, I had to bust out a custom string allocation engine. It's not very pretty and I promise I'll fix it some day... So don't worry too much about the StringUtils stuff. I just wanted to put up a working example of how to efficiently send dynamic messages, because that's a real-world scenario. 

