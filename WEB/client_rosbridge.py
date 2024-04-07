import json
import websocket
from threading import Thread
from time import sleep



class WebSocketApp(Thread):
    def __init__(self, ip_rasp: str = "0.0.0.0", port_rasp: int = 9090):
        Thread.__init__(self)
        self.ip_server = ip_rasp
        self.port_server = port_rasp
        self.ws: websocket = None
        self.topic_data: dict = {}
        self.topic_to_subscribe: str = None
        self.orient: dict = {}

    def run(self) -> None:
        self.connect()

    def connect(self):
        self.ws: websocket = websocket.WebSocketApp(f"ws://{self.ip_server}:{self.port_server}",
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = self.on_open
        self.ws.run_forever()
    
    def reconnect(self):
        while not self.ws or not self.ws.sock or not self.ws.sock.connected:
            print("[INFO] Tentative de reconnexion...")
            sleep(5)  # Délai avant de retenter la connexion
            self.connect()

    def on_message(self, ws:  websocket, message: json) -> None:
        data: dict = json.loads(message)
        topic: str = data.get('topic')
        if topic and topic == self.topic_to_subscribe:
            self.topic_data[topic] = data['msg']
            if self.topic_data and topic == "/odometry/filtered":
                self.orient = self.topic_data[topic]["pose"]["pose"]["orientation"]
            self.unsubscribe(topic)

    def on_error(self, ws: websocket, error: str) -> None:
        print("[INFO][ON_ERROR] Erreur :", error)
        sleep(5)  # Attendre avant de retenter la connexion
        self.reconnect()


    def on_close(self, ws: websocket) -> None:
        print("[INFO][ON_CLOSE] Connexion fermée. Tentative de reconnexion...")
        sleep(5)
        self.reconnect()


    def on_open(self, ws: websocket) -> None:
        print("[INFO][ON_OPEN] Connexion établie avec le serveur Rosbridge")

    def publish(self, topic: str, message_type: str, message: dict) -> None:
        if not self.ws or not self.ws.sock:
            print("[INFO][PUBLISH] WebSocket n'est pas connecté. Tentative de reconnexion...")
            return

        publish_message: dict = {
            "op": "publish",
            "topic": topic,
            "msg": message,
            "type": message_type
        }
        self.ws.send(json.dumps(publish_message))

    def subscribe(self, topic: str, message_type: str) -> None:
        if not self.ws or not self.ws.sock or not self.ws.sock.connected:
            print("[INFO][SUBSCRIBE] WebSocket n'est pas connecté. Tentative de reconnexion...")
            return
        
        print("[INFO][SUBSCRIBE]")
        self.topic_to_subscribe: str = topic
        subscribe_message: dict = {
            "op": "subscribe",
            "topic": topic,
            "type": message_type
        }
        self.ws.send(json.dumps(subscribe_message))

    def unsubscribe(self, topic: str) -> None:
        print("[INFO][UNSUBSCRIBE]")
        unsubscribe_message: dict = {
            "op": "unsubscribe",
            "topic": topic
        }
        self.ws.send(json.dumps(unsubscribe_message))
        self.topic_to_subscribe = None

# Instanciation du client WebSocket

