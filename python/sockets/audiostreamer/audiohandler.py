import pyaudio
import socket
import os
from dataclasses import dataclass

HOME_AUDIO_PATH = os.path.join(os.getcwd(), 'audio')


@dataclass
class StreamReceiver:
    sock: socket.socket
    stream: pyaudio.Stream


class AudioSender:

    def __init__(self):
        self.audio = pyaudio.PyAudio()

    def open_audio_stream(self, audio_path: str) -> pyaudio.Stream:
        return self.audio.open(format=pyaudio.paInt16, channels=2,
                               rate=44100, output=True)


class AudioReceiver:
    pass
