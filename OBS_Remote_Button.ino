// Ideas from:
// https://github.com/illusion-pasture-program/ESP8266-OBS-Websocket-Client/blob/master/ESP8266-OBS-WebSocketClient_Demo.ino
// https://www.instructables.com/NodeMCU-ProjectButton-Control-LED/

// Youtube video: 


#define LED 5 // D1(gpio5)
#define BUTTON 4 //D2(gpio4)
int switchState = 0; // actual read value from pin4
int oldSwitchState = 0; // last read value from pin4
int lightsOn = 0; // is the switch on = 1 or off = 0


#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "OOZTEST";    // Nome della vostra wifi
const char* password = "diegodiego";   //pass della vostra wifi

char obs_host[] = "192.168.1.188";   // ip del computer che esegue obs
uint16_t obs_port = 4455;            // porta di obs web socket 4455 è di default

WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections for websockets and http posts
WiFiClient client;

void setup() {

 pinMode(BUTTON, INPUT); // push button 
 pinMode(LED, OUTPUT); // anything you want to control using a switch e.g. a Led


  Serial.begin(115200); 
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
  

  // Connect to the websocket server
  if (client.connect(obs_host, obs_port)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }

  // Handshake with the server
  webSocketClient.path = "/";
  webSocketClient.host = obs_host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
    //Send OBS confirmation 
    webSocketClient.sendData("{\"op\":1,\"d\":{\"rpcVersion\":1}}");
  } else {
    Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }
 
}
 
void loop() {



 switchState = digitalRead(BUTTON); // read the pushButton State
 if (switchState != oldSwitchState) // catch change
 {
 oldSwitchState = switchState;
 if (switchState == HIGH)
 {
 // toggle
 lightsOn = !lightsOn;
 }
 }
 if(lightsOn)
 {
 digitalWrite(LED, HIGH); // set the LED on
    webSocketClient.sendData("{\"op\":6,\"d\":{\"requestId\":\"616\",\"requestType\":\"StartRecord\"}}");
 } else {
 digitalWrite(LED, LOW); // set the LED off
webSocketClient.sendData("{\"op\":6,\"d\":{\"requestId\":\"617\",\"requestType\":\"StopRecord\"}}");




  String data;
  
  //Not a practical example, but this code sets the active scene to the scene named "Enter Scene Name" and does so every 5 seconds.
  //In actual use, you'd want to make this in response to a button press, a sensor level getting tripped, etc.
 
  // if (client.connected()) {
    // Set the active scene based on scene name. Implemented properly, each request would have a unique "requestId", but OBS will accept the command even with a duplicate UID
    // For details how websocket messages to send, see the official documetnation here https://github.com/obsproject/obs-websocket/blob/master/docs/generated/protocol.md
   // webSocketClient.sendData("StartStopRecording");
   //  webSocketClient.sendData("{\"op\":6,\"d\":{\"requestId\":\"615\",\"requestType\":\"SetCurrentProgramScene\",\"requestData\":{\"sceneName\":\"Attesa\"}}}");

    
    webSocketClient.getData(data);
  //  if (data.length() > 0) {       
      Serial.print("Received data: ");
      Serial.println(data);
      delay(1);
  //  }
 // } else {
  //  Serial.println("Client disconnected.?");
 //   while (1) {
      // Hang on disconnect.
  //  }
 // }
  
  // wait to fully let the client disconnect
 delay(250);
 yield();
  
}  }
