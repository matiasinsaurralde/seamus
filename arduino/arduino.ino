#include <SPI.h>
#include <Ethernet.h>
#define BUFSIZ 7

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
  
  char recvLine[BUFSIZ];
  int index = 0;
  
  EthernetClient client = server.available();
  
  if (client) {
    
    index = 0;
    
    while( client.connected() ) {
      if( client.available() ) {
        char c = client.read();
        
        if ( c != '\n' && c != '\r' ) {
          recvLine[ index ] = c;
          index++;
          
          if( index >= BUFSIZ )
            index = BUFSIZ -1;
          continue;
        };
        
        recvLine[ index ] = 0;
        
        char actionStr[2] = { recvLine[0], '\0' };
        char delayTimeStr[ 5 ] = { recvLine[2], recvLine[3], recvLine[4], recvLine[5], '\0' };
        int action = atol( actionStr );
        int delayTime = atol( delayTimeStr );
        
        drive( action, delayTime );
              
        break;
      };
    };

  }
}



