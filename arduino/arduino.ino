#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 1, 200);

EthernetServer server(9000);
boolean isConnected = false;

void setup() {

  Ethernet.begin( mac, ip );

  server.begin();

  Serial.begin(9600);
  
}

void loop() {
  EthernetClient client = server.available();
  
  if (client) {
    if( !isConnected ) {
      client.flush();
      client.println("SEAMUS");
      isConnected = true;
    };
    
    if( client.available() > 0 ) {
      char option = client.read();
      Serial.write("selecciono: ");
      Serial.write( option );
      Serial.write("\n");
    };

  }
}



