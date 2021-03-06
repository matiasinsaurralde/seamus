package main

import ( "net/http"
         "strconv"
         "strings"
         "net"
         "fmt" )

func controlHandler( w http.ResponseWriter, r *http.Request, conn net.Conn ) {
  http.ServeFile( w, r, "control.html" )
  command := strings.Replace( r.URL.Path, "/", "", 1 )
  switch command {
    case "accelerate": sendCommand( conn, 7 )
    case "reverse": sendCommand( conn, 6 )
    case "left": sendCommand( conn, 5 )
    case "right": sendCommand( conn, 4 )
  }
}

func sendCommand( conn net.Conn, command int ) {
  fmt.Fprintf( conn, strconv.Itoa( command ) + "," + strconv.Itoa( 1000 ) + "\n" )
}

func main() {

  conn, _ := net.Dial( "tcp", "192.168.1.200:9000" )

  http.HandleFunc( "/", func( w http.ResponseWriter, r *http.Request) { controlHandler(w, r, conn) })
  http.ListenAndServe( ":8000", nil )

}
