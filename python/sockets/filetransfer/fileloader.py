import os


class FileLoader:
    @staticmethod
    def load(filename) -> bytes:
        with open(filename) as f:
            return f.read()

    @staticmethod
    def list() -> list:
        return list(filter(lambda file: not file.endswith(".py") ,os.listdir(os.curdir)))
