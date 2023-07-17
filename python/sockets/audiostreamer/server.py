import socket
import asyncio
from audiohandler import AudioSender


class Server:

    def __init__(self, host: str, port: int, family: int, sock_type: int):
        self.host = host
        self.port = port
        self.family = family
        self.sock_type = sock_type
        self.clients: list[socket.socket] = []
        self.audio_sender = AudioSender()

    def _get_socket(self) -> socket.socket:
        return socket.socket(self.family, self.sock_type)

    def _bind_socket(self, sock) -> socket.socket:
        sock.bind((self.host, self.port))
        return sock

    async def audio_loop(self) -> None:
        while True:
            await asyncio.sleep(1)

    def run(self):
        sock = self._get_socket()
        sock = self._bind_socket(sock)
        sock.listen()
        while True:
            cli = sock.accept()
            self.clients.append(cli)
            print(f"Client {cli[0]} connected")
            print(f"Total clients: {len(self.clients)}")


if __name__ == '__main__':
    server = Server('localhost', 5454, socket.AF_INET, socket.SOCK_STREAM)
    server.run()
