
#code STATUS :  DRAFT

from threading import Thread
from socket import socket, AF_INET, SOCK_DGRAM
from cv2 import imdecode, IMREAD_COLOR
from numpy import frombuffer, uint8

SERVER_IP = "0.0.0.0"
SERVER_PORT = 7070

class WebVideoApp(Thread):
    def __init__(self):
        super().__init__()
        self.image = None
        self.sock = socket(AF_INET, SOCK_DGRAM)
        sock.bind((SERVER_IP, SERVER_PORT))

    def run(self):
        while True:
            data, addr = sock.recvfrom(65535)  # buffer size is 65535 bytes
            image = imdecode(frombuffer(data, uint8), IMREAD_COLOR)
            self.image = image
            print(f"[DEBUG] Image received from {addr}")
# Usage
video_stream = WebVideoApp()
video_stream.start()



