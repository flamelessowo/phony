import socket, threading

ADDR = '127.0.0.1'
PORT = 8000
SIZE = 1024

connections = []

def handle_conn(cli_sock: socket.socket, address: str) -> None:
    while True:
        try:
            msg = cli_sock.recv(SIZE)
            if msg:
                print(f'{address[0]}:{address[1]} - {msg.decode()}')
                msg_to_send = f'From {address[0]}:{address[1]} - {msg.decode()}'
                broadcast(msg_to_send, cli_sock)

        except Exception as e:
            print(f'Error to handle user connection: {e}')
            break

def broadcast(msg: str, conn: socket.socket) -> None:
    for cli in connections:
        if conn != cli:
            try:
                cli.send(msg.encode())
            except Exception as e:
                print('Error broadcasting message: {e}')
    

def host() -> None:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.bind((ADDR, PORT))
        sock.listen(15)
        print(f'Socket created with addr: {ADDR}:{PORT}')

        while True:
            sd, addr = sock.accept()
            connections.append(sd)
            threading.Thread(target=handle_conn, args=(sd, addr)).start()

if __name__ == '__main__':
    host()
