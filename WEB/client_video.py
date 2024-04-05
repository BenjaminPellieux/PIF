
#code STATUS :  DRAFT

from threading import Thread
from socket import socket, AF_INET, SOCK_DGRAM
from cv2 import imdecode, IMREAD_COLOR, imencode, imwrite
from numpy import frombuffer, uint8
from time import sleep

SERVER_IP = "0.0.0.0"
SERVER_PORT = 7070

class WebVideoApp(Thread):
    def __init__(self):
        super().__init__()
        self.image = None
        self.sock = socket(AF_INET, SOCK_DGRAM)
        self.sock.bind((SERVER_IP, SERVER_PORT))

    def run(self):
        while True:
            data, addr = self.sock.recvfrom(65535)  # buffer size is 65535 bytes
            image = imdecode(frombuffer(data, uint8), IMREAD_COLOR)
            self.image = image
            imwrite('tmp/PIF.jpg', self.image)

video_stream = WebVideoApp()
video_stream.start()



