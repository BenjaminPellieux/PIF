
#code STATUS :  DRAFT

from threading import Thread
from socket import socket, AF_INET, SOCK_DGRAM
from cv2 import imdecode, IMREAD_COLOR, imwrite
from numpy import frombuffer, uint8
from time import sleep

class WebVideoApp(Thread):
    def __init__(self, server_ip: str = "0.0.0.0", server_port: int = 7070 ):
        super().__init__()
        self.image = None
        self.sock = socket(AF_INET, SOCK_DGRAM)
        self.sock.bind((server_ip, server_port))

    def run(self):
        while True:
            data, _ = self.sock.recvfrom(65535)  # buffer size is 65535 bytes
            image = imdecode(frombuffer(data, uint8), IMREAD_COLOR)
            self.image = image
            imwrite('tmp/PIF.jpg', self.image)
            sleep(0.5)




