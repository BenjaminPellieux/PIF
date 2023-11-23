import json
import websocket
from threading import Thread
from time import sleep
# IP_RASP = "192.168.131.1"
IP_RASP = "10.8.0.3"
PORT = "9090"
# PORT = "11311"



class WebSocketApp(Thread):
    def __init__(self):
        Thread.__init__(self)
        self.ws = None
        self.topic_data = {}
        self.topics_to_subscribe = {}
        self.orient: dict = {}


    def run(self) -> None:
        self.connect()

    def connect(self):
        self.ws = websocket.WebSocketApp(f"ws://{IP_RASP}:{PORT}",
                                         on_message = self.on_message,
                                         on_error   = self.on_error,
                                         on_close   = self.on_close)
        self.ws.on_open = self.on_open
        self.ws.run_forever()

    def on_message(self, ws, message):
        data = json.loads(message)
        topic = data.get('topic')
        # print(f"[DEBUG] {topic=}")
        if topic in self.topics_to_subscribe:
            self.topic_data[topic] = data['msg']
            if topic == "/odometry/filtered":
                self.orient = self.topic_data[topic]["pose"]["pose"]["orientation"]

    def on_error(self, ws, error):
        print("Erreur :", error)
        sleep(5)
        self.connect()

    def on_close(self, ws):
        print("Connexion fermée. Tentative de reconnexion...")
        sleep(5)
        self.connect()

    def on_open(self, ws):
        print("Connexion établie avec le serveur Rosbridge")
        for topic, message_type in self.topics_to_subscribe.items():
            print(f"[INFO] Subscribing to topic {topic}")
            self.subscribe(topic, message_type)

    def subscribe(self, topic, message_type):
        if not self.ws or not self.ws.sock:
            print("WebSocket n'est pas connecté.")
            return

        self.topics_to_subscribe[topic] = message_type
        self.topic_data[topic] = {}
        subscribe_message = {
            "op": "subscribe",
            "topic": topic,
            "type": message_type
        }
        self.ws.send(json.dumps(subscribe_message))

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

    def unsubscribe(self, topic):
        if topic in self.topics_to_subscribe:
            unsubscribe_message = {
                "op": "unsubscribe",
                "topic": topic
            }
            self.ws.send(json.dumps(unsubscribe_message))
            del self.topics_to_subscribe[topic]

# Instanciation du client WebSocket
ws_app = WebSocketApp()
ws_app.topics_to_subscribe["/odometry/filtered"]=  "nav_msgs/Odometry"
ws_app.topics_to_subscribe["/navsat/fix"] =  "sensor_msgs/NavSatFix"
ws_app.start()
# Exemple d'abonnement à plusieurs topics

