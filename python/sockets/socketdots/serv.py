import threading
import socket as sock
from logging import getLogger

logger = getLogger('Net err logger')
HOST_ADDR = "127.0.0.1"
HOST_PORT = 8000
DGRAM_SIZE = 1024

class ServSocket:
    client_addr: tuple[str, int]
    clienttwo_addr: tuple[str, int]
    sd: sock.socket

    def __init__(self) -> None:
        sd = sock.socket(family=sock.AF_INET, type=sock.SOCK_DGRAM)
        sd.bind((HOST_ADDR, HOST_PORT))
        print(f'Runned socket with port: {HOST_PORT}')
        self.sd = sd

    def host(self):
        print('Awaiting... for Player 1')
        _, addr = self.sd.recvfrom(DGRAM_SIZE)
        print('Player 1 connected!')
        print('Awaiting... for Player 2')
        _, addr2 = self.sd.recvfrom(DGRAM_SIZE)
        print('Player 2 connected!')
        self.client_addr = addr
        self.clienttwo_addr = addr2
        return self

    def handleMoves(self, cli_addr, index) -> None:
        while True:
            logger.warning('Awaiting for data...')
            data, addr = self.sd.recvfrom(DGRAM_SIZE)
            logger.warning('Got data!')
            if not self.ensure_request_addr(addr):
                logger.warning(f'got request from wrong address: {addr}.\nignoring...')
                return
            print(data.decode())
            self.sd.sendto(b'bruh\n', self.client_addr)
            print(f'received: from {addr}')

    def ensure_request_addr(self, req_addr: tuple[str, int]) -> bool:
        return ((self.client_addr[0] == req_addr[0] and self.client_addr[1] == req_addr[1]) or
        (self.clienttwo_addr[0] == req_addr[0] and self.clienttwo_addr[1] == req_addr[1]))

if __name__ == '__main__':
    serv = ServSocket().host()
    threading.Thread(target=serv.handleMoves, args=(serv.client_addr, 0))
    threading.Thread(target=serv.handleMoves, args=(serv.clienttwo_addr, 1))


