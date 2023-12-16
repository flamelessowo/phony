import socket, threading
from server import ADDR, PORT, SIZE

SIZE = 1024
ADDR = '127.0.0.1'
PORT = 8000

def handle_messages(conn: socket.socket):
    while True:
        try:
            msg = conn.recv(SIZE)
            if msg:
                print(msg.decode())
            else:
                conn.close()
                break
        except Exception as e:
            print(f'Error handling message from server: {e}')
            conn.close()
            break


def run_client():
    clisd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clisd.connect((ADDR, PORT))
    threading.Thread(target=handle_messages, args=[clisd]).start()
    print('Connected to chat')
    while True:
        msg = input()
        if msg == 'quit':
            break
        clisd.send(msg.encode())

    clisd.close()

if __name__ == '__main__':
    run_client()
