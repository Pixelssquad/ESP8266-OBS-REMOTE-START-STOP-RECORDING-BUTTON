## Websocket Client for ESP-8266
The ESP8266-Websocket library allows you to communicate directly with the native OBS (v 28+) Websocket server using an ESP-8266. This example sketch is a fork of the library's client demo, and is a bare-bones implementation of sending commands to and getting data from an OBS Websocket server.

### Getting started
Install the library to the "libraries" folder in your Arduino sketchbook folder and update the host to match that of your OBS websocket server.
https://github.com/morrissinger/ESP8266-Websocket/

### Notes
This demo does not properly implement all features of communicating with the OBS Websocket server. Unique message IDs, as specified by the protocol, are not generated. However, OBS successfully processes the commands even without dynamically generated IDs. Because the example works without unique message IDs, they are kept static in the interest of providing the simplest possible demo of ESP-8266 to OBS communication.

If using Windows and cannot connect to OBS, make sure your firewall rules are set up to allow inbound and outbound connections to/from OBS.

### Credits
Thanks to Branden for his great library and the sample Websocket client example. This code is just a specific OBS implementation of his more general websocket client code.
