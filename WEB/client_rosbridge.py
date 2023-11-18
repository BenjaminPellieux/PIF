import json
import websocket
from threading import Thread

# Interval en secondes pour l'envoi des données
SEND_INTERVAL = 2

# Dictionnaire pour stocker la dernière valeur de chaque topic
last_topics_values = {}
IP_RASP = "10.8.0.3"

# Timestamp de la dernière fois où les données ont été envoyées
last_send_time = 0
ws_app = None

class WebSocketApp(Thread):
    def __init__(self):
        Thread.__init__(self)
        self.daemon = True
        self.ws = None
        self.topic_data = {}
        self.topic_to_subscribe = None

    def run(self):
        self.ws = websocket.WebSocketApp(f"ws://{IP_RASP}:9090",
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = self.on_open
        self.ws.run_forever()

    def on_message(self, ws, message):
        data = json.loads(message)
        topic = data.get('topic')
        if topic and topic == self.topic_to_subscribe:
            self.topic_data[topic] = data['msg']
            self.unsubscribe(topic)

    def on_error(self, ws, error):
        print("Erreur :", error)

    def on_close(self, ws):
        print("Connexion fermée")

    def on_open(self, ws):
        print("Connexion établie avec le serveur Rosbridge")

    def subscribe(self, topic, message_type):
        self.topic_to_subscribe = topic
        subscribe_message = {
            "op": "subscribe",
            "topic": topic,
            "type": message_type
        }
        self.ws.send(json.dumps(subscribe_message))

    def unsubscribe(self, topic):
        unsubscribe_message = {
            "op": "unsubscribe",
            "topic": topic
        }
        self.ws.send(json.dumps(unsubscribe_message))
        self.topic_to_subscribe = None

# Instanciation du client WebSocket
ws_app = WebSocketApp()
ws_app.start()
