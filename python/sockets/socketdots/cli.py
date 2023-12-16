import socket

class Client:
    def __init__(self) -> None:
        self.cli = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.serv = "127.0.0.1"
        self.port = 8000
        self.serv_addr = (self.serv, self.port)
        self.pos = self.connect()

    def get_pos(self):
        return self.pos
    
