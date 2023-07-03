package main

import (
	"fmt"
	"log"
	"net"
)

func main() {
	ln, err := net.Listen("tcp", "127.0.0.1:8000")
	if err != nil {
		log.Fatal(err)
	}
	for {
		fmt.Println("connected")
		conn, err := ln.Accept()
		fmt.Println(conn)
		if err != nil {
			log.Fatal(err)
		}
	}
}
