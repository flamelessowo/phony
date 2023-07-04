import socket

ADDRESS = "127.0.0.1"
PORT = 8080

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((ADDRESS, PORT))
    files: bytes = sock.recv(1024)
    print(files.decode())
    msg: str = input("Enter filename: ")
    sock.sendall(msg.encode())
