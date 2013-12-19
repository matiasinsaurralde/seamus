#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 1, 200);

EthernetServer server(9000);
boolean isConnected = false;

int accelerateP = 7;
int reverseP = 6;
int turnLeftP = 5;
int turnRightP = 4;


void setup() {

  Ethernet.begin( mac, ip );

  server.begin();

  pinMode( accelerateP, OUTPUT );
  digitalWrite (accelerateP, HIGH );
  pinMode( reverseP, OUTPUT );
  digitalWrite( reverseP, HIGH );

  pinMode( turnLeftP, OUTPUT );
  digitalWrite( turnLeftP, HIGH );
  pinMode( turnRightP, OUTPUT );
  digitalWrite( turnRightP, HIGH );

  Serial.begin(9600);
  
}

void drive( int action, int time = 1000 ) {
  digitalWrite( action, LOW );
  delay( time );
  digitalWrite( action, HIGH );
};

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



