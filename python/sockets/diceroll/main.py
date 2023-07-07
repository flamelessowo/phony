from server import Server
import socket


def main():
    server = Server('localhost', 5432, socket.AF_INET, socket.SOCK_STREAM, 2)
    server.run()


if __name__ == '__main__':
    main()
