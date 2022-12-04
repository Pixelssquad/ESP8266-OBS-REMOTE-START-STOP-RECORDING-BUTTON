#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "SSID HERE";
const char* password = "PASSWORD HERE";

char obs_host[] = "OBS IP HERE - for example 192.168.1.100";
uint16_t obs_port = 4455;

WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections for websockets and http posts
WiFiClient client;

void setup() {
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
  String data;
  
  //Not a practical example, but this code sets the active scene to the scene named "Enter Scene Name" and does so every 5 seconds.
  //In actual use, you'd want to make this in response to a button press, a sensor level getting tripped, etc.
 
   if (client.connected()) {
    // Set the active scene based on scene name. Implemented properly, each request would have a unique "requestId", but OBS will accept the command even with a duplicate UID
    // For details how websocket messages to send, see the official documetnation here https://github.com/obsproject/obs-websocket/blob/master/docs/generated/protocol.md
    webSocketClient.sendData("{\"op\":6,\"d\":{\"requestId\":\"615\",\"requestType\":\"SetCurrentProgramScene\",\"requestData\":{\"sceneName\":\"Enter Scene Name\"}}}");
  
    
    webSocketClient.getData(data);
    if (data.length() > 0) {       
      Serial.print("Received data: ");
      Serial.println(data);
      delay(1);
    }
  } else {
    Serial.println("Client disconnected.");
    while (1) {
      // Hang on disconnect.
    }
  }
  
  // wait to fully let the client disconnect
 delay(5000);
 yield();
  
}
