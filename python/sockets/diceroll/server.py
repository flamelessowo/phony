import socket
from helpers import roll_de_dice


class Server:

    def __init__(self, host: str, port: int, family: int, type: int, max_clients: int):
        self.host = host
        self.port = port
        self.family = family
        self.type = type
        self.max_clients = max_clients
        self.clients = []

    def _get_socket(self) -> socket.socket:
        return socket.socket(self.family, self.type)

    def run(self):
        sock: socket.socket = self._get_socket()
        sock.bind((self.host, self.port))
        sock.listen(self.max_clients)
        while True:
            try:
                cli_sock, cli_addr = sock.accept()
                print(cli_sock)
                self.clients.append(cli_sock)
                if (len(self.clients) == 2):
                    for sock in self.clients:
                        sock.sendall(b"2 clients connected")
                    break
            except socket.error:
                pass
