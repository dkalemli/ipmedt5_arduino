#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "KeuperIOT";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "exPnPJ8gAPhF3Esh";     // The password of the Wi-Fi network

boolean connected;

WiFiClient client;    

float humidityData = 100;
float temperatureData = 20;
boolean getRequest = false;
const int BUTTON = 12;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(13, HIGH);
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  attachInterrupt(digitalPinToInterrupt(BUTTON), alarm, FALLING);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  IPAddress ip (192, 168, 0, 1); // The remote ip to ping
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

ICACHE_RAM_ATTR void alarm(){
  getRequest = true;
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    digitalWrite(13, HIGH); 
    Serial.println("Disconnected");
    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
      delay(1000);
      Serial.print(++i); Serial.print(' ');
    }
  } else {
    digitalWrite(13, LOW);
    if (getRequest){
      sendGetRequest();
      getRequest = false;
    }
  }
}

void sendGetRequest()   //CONNECTING WITH MYSQL
{
 Serial.println("sending");
 client.connect("83.85.113.219", 80);
  Serial.println("sending get request");
  client.print("GET /school/dht11.php?humidity=");
  client.print(20);
  client.print("&temperature=");
  client.print(20);
  client.print(" ");      //SPACE BEFORE HTTP/1.1
  client.print("HTTP/1.1");
  client.println();
  client.println("Host: 83.85.113.219");
  client.println("Connection: close");
  client.println();

}
