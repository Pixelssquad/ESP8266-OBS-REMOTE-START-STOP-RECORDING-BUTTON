## Websocket Client for ESP-8266

An example sketch that lets you communicate directly with the native OBS (v 28+) Websocket server using a ESP-8266. This sketch uses the ESP8266-Websocket library and is a fork of the libraries client demo. It is a bare-bones example of sending commands to, and getting data from an OBS Websocket server.

https://github.com/morrissinger/ESP8266-Websocket/

### Getting started

Install the library to "libraries" folder in your Arduino sketchbook folder. Update the host to match that of your OSB websocket server.

### Notes
This demo does not properly implement all features of communicating with the OBS Websocket server. Specifically, unique messages IDs are not generated as specified by the protocol. OBS successfully processes the commands, even without dynamically generated IDs. Because the example works without unique message IDs, I kept them static in the spirit of the simplest possible demo of ESP-8266 to OBS communication.

If using Windows and this does not connect to OBS, make sure you have the firewall rules setup to allow inbound and oubound connections to/from OBS.

### Credits
Thanks to Branden for his great library and the sample Websocket client example. This code is just a specific OBS implementation of his more general websocket client code.
