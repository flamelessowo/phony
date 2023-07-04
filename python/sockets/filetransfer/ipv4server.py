import socket

from fileloader import FileLoader

ADDRESS = "127.0.0.1"
PORT = 8080

if __name__ == "__main__":
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.bind((ADDRESS, PORT))
        sock.listen(1)
        conn, addr = sock.accept()
        with conn:
            while True:
                conn.sendto(','.join(FileLoader.list()).encode("UTF-8"), addr)
                fname: bytes = conn.recv(1024).decode()
                file: bytes = FileLoader.load(fname)
                print(file)
                with open(f"{fname}a", "wb") as f:
                    f.write(file)
                break
