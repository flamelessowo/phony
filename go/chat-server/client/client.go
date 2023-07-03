package client

type messageHandler func(string)

type Client interface{
	Dial(address string) error
	Start()
	Close()
	Send(command interface{}) error
	SetName(name string) error
	SendMessage(message string) error
}
