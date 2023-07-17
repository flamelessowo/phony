import socket


class Client:
    def __init__(self, host, port, family, sock_type):
        self.host = host
        self.port = port
        self.family = family
        self.sock_type = sock_type

    def _get_socket(self) -> socket.socket:
        return socket.socket(self.family, self.sock_type)

    def _connect_socket(self, sock: socket.socket) -> socket.socket:
        sock.connect((self.host, self.port))
        return sock

    def run(self):
        sock = self._get_socket()
        sock = self._connect_socket(sock)
        while True:
            pass


if __name__ == '__main__':
    client = Client('localhost', 5454, socket.AF_INET, socket.SOCK_STREAM)
    client.run()
