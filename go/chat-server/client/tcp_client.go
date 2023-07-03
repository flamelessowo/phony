package client

import (
	"io"
	"log"
	"net"

	"chatserver/tools"
)

type TcpClient struct {
	conn net.Conn
	cmdReader *tools.CommandReader
	cmdWriter *tools.CommandWriter
	name string
	incoming chan tools.MessageCommand
}
