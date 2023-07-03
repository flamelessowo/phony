package tools

import "errors"

var (
	UnknownCommand = errors.New("UnknownCommand")
)

type SendCommand struct {
	Message string
}

type NameCommand struct {
	Name string
}

type MessageCommand struct {
	Name string
	Message string
}
