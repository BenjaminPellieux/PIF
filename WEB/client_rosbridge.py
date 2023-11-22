import json
import websocket
from threading import Thread
from time import sleep

IP_RASP = "10.8.0.3"


class WebSocketApp(Thread):
    def __init__(self):
        Thread.__init__(self)
        self.ws: websocket = None
        self.topic_data: dict = {}
        self.topic_to_subscribe: str = None
        self.orient: dict = {}

    def run(self) -> None:
        self.connect()

    def connect(self):
        self.ws: websocket = websocket.WebSocketApp(f"ws://{IP_RASP}:9090",
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = self.on_open
        self.ws.run_forever()

    def on_message(self, ws:  websocket, message: json) -> None:
        data: dict = json.loads(message)
        topic: str = data.get('topic')
        if topic and topic == self.topic_to_subscribe:
            self.topic_data[topic] = data['msg']
            if self.topic_data:
                self.orient = self.topic_data[topic]["pose"]["pose"]["orientation"]
            self.unsubscribe(topic)

    def on_error(self, ws: websocket, error: str) -> None:
        print("Erreur :", error)
        sleep(5)  # Attendre avant de retenter la connexion
        self.connect()  # Tentative de reconnexion

    def on_close(self, ws: websocket) -> None:
        print("Connexion fermée. Tentative de reconnexion...")
        self.on_error(self.ws)

    def on_open(self, ws: websocket) -> None:
        print("Connexion établie avec le serveur Rosbridge")

    def publish(self, topic: str, message_type: str, message: dict) -> None:
        if not self.ws or not self.ws.sock:
            print("WebSocket n'est pas connecté. Tentative de reconnexion...")
            self.on_close(self.ws)
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
            print("WebSocket n'est pas connecté. Tentative de reconnexion...")
            self.on_close(self.ws)
            return

        self.topic_to_subscribe: str = topic
        subscribe_message: dict = {
            "op": "subscribe",
            "topic": topic,
            "type": message_type
        }
        self.ws.send(json.dumps(subscribe_message))

    def unsubscribe(self, topic: str) -> None:
        unsubscribe_message: dict = {
            "op": "unsubscribe",
            "topic": topic
        }
        self.ws.send(json.dumps(unsubscribe_message))
        self.topic_to_subscribe = None

# Instanciation du client WebSocket
ws_app: WebSocketApp = WebSocketApp()
ws_app.start()
