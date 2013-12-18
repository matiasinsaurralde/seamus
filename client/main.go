package main

import ( "fmt"
         "net"
         "os" )

func main() {
  fmt.Println("SEAMUS");
  conn, _ := net.Dial( "tcp", os.Args[1] + ":9000" )
  fmt.Fprintf( conn, "" )
  fmt.Fprintf( conn, os.Args[2] )
}
