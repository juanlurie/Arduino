#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 177);
IPAddress gateway(192,168,1, 1);
IPAddress subnet(255, 255, 255, 0);

int led = 8;
int ledState = HIGH;
EthernetServer server(23);
boolean alreadyConnected = false;

void setup() {
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
   pinMode(led, OUTPUT); 
   digitalWrite(led, ledState);
}

void loop() {
  EthernetClient client = server.available();

  if (client) {
    if (!alreadyConnected) {
      client.flush();    
      Serial.println("We have a new client");
      alreadyConnected = true;
    } 

    if (client.available() > 0) {
      char thisChar = client.read();
      Serial.write(thisChar);
      if(thisChar == '0')
      {
        ledState = !ledState;
        digitalWrite(led, ledState);
      }
    
      client.write(ledState + "\r\n");
     
      Serial.write(thisChar);
    }
  }
}



