import socket
from helpers import roll_de_dice


class Client:
    def __init__(self, host: str, port: int, family: int, type: int):
        self.host = host
        self.port = port
        self.family = family
        self.type = type

    def _get_socket(self) -> socket.socket:
        return socket.socket(self.family, self.type)

    def connect(self) -> socket.socket:
        sock: socket.socket = self._get_socket()
        sock.connect((self.host, self.port))
        return sock


if __name__ == '__main__':
    client = Client('localhost', 5432, socket.AF_INET, socket.SOCK_STREAM)
    sock: socket.socket = client.connect()
    welcome_message: str = sock.recv(1024).decode('utf-8')
    print(welcome_message)
    while True:
        pass
