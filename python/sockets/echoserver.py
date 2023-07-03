import socket

HOST: str = '127.0.0.1'
PORT: int = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.bind((HOST, PORT))
    sock.listen()
    conn, addr = sock.accept()
    with conn:
        print(f"Connected by {addr}")
        while True:
            data: bytes = conn.recv(1024)
            if not data:
                break
            conn.sendall(data)
