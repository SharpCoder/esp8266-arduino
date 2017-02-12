# esp8266-arduino
An arduino library for doing basic HTTP commands with the ESP8266 chip.

Currently, my library only supports /GET. However, that should change soon as I need
to actually make a POST request for my project. I wanted to get this open source library up
though, as an example for how to use the ESP8266 module with the arduino. Specifically wrt
making http requests. Which is probably what most people use it for.


The only (admittedly big) missing feature here is actually ip-address lookup.
You'll have to hard-code an ip address which you want to access.

## Supported protocols

* GET

Yeah that's a pathetic list. Hopefully more to come!

## Using this library
You will need to go into the main.ino file, update the HttpMessage object and supply your own constants for **NETWORK_NAME_HERE** and **NETWORK_PASSWORD_HERE**.

I have added my own kind of Serial.readStringUntil()  method because the default one that arduino provides wasn't cutting it for me. It has some retry logic and seems to work pretty well for my purposes. You may find the *timeout* needs to be tweaked a bit. If you get a lot of "Error condition has been met" messages, that's probably why.