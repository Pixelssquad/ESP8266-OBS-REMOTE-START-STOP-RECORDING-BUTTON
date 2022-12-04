## Websocket Client and Server for ESP-8266

An example sketch that lets you communicate directly with the native OBS (v 27+) Websocket server using a ESP-8266. This sketch uses the ESP8266-Websocket library and is a fork of the libraries client demo.

https://github.com/morrissinger/ESP8266-Websocket/

### Getting started

Install the library to "libraries" folder in your Arduino sketchbook folder. Update the host to match that of your OSB websocket server.

### Notes
Inside of the WebSocketServer class there is a compiler directive to turn on support for the older "Hixie76" standard. If you don't need it, leave it off as it greatly increases the memory required.

Because of limitations of the current Arduino platform (Uno at the time of this writing), this library does not support messages larger than 65535 characters. In addition, this library only supports single-frame text frames. It currently does not recognize continuation frames, binary frames, or ping/pong frames.

### Credits
Thanks to Branden for his great library and the sample Websocket client exmple. This code is just a specific OBS implementation of his more general websocket client code.
