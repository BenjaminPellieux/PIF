import json
from lib_topic import *
import websocket
from threading import Thread
from numpy import frombuffer, uint8
from cv2 import imwrite
from base64 import b64decode


class WebSocketApp(Thread):
    def __init__(self, ip_rasp: str = "0.0.0.0", port_rasp: int = 9090):
        super().__init__()
        self.ip_server = ip_rasp
        self.port_server = port_rasp
        self.ws: websocket = None
        self.topic_data: dict = {}
        self.topic_to_subscribe: dict = topic_type_dict
        self.orient: dict = {}

    def run(self) -> None:
        self.ws: websocket = websocket.WebSocketApp(f"ws://{self.ip_server}:{self.port_server}",
                                         on_message=self.on_message,
                                         on_error=self.on_error,
                                         on_close=self.on_close)
        self.ws.on_open = self.on_open
        
        self.ws.run_forever()
        
    
    def reconnect(self):
        print("[INFO] Tentative de reconnexion...")
        self.run()

    def on_message(self, ws:  websocket, message: json) -> None:
        data = json.loads(message)
        topic = data.get('topic')
        if topic and topic in self.topic_to_subscribe:
            self.topic_data[topic] = data['msg']    
            if self.topic_data and topic == "/odometry/filtered":
                self.orient = self.topic_data[topic]["pose"]["pose"]["orientation"]
            elif self.topic_data and topic == "/pif/waste/frame":
                self.image_callback(data['msg'])

    
    def image_callback(self, msg: dict):

        np_arr = frombuffer(b64decode(msg['data']), dtype = uint8)        
        if msg["encoding"] == 'rgb8':
            image_np = np_arr.reshape((msg["height"], msg["width"], 3))
        else:
            print("[ERROR][IMAGE_CALLBACK]Encodage non pris en charge: {}".format(msg["encoding"]))
            return
        
        imwrite('static/tmp/PIF.jpg', image_np)



    def on_error(self, ws: websocket, error: str) -> None:
        print("[INFO][ON_ERROR] Erreur :", error)

    def on_close(self,  ws:  websocket) -> None:
        print("[INFO][ON_CLOSE] Connexion fermée. Tentative de reconnexion...")


    def on_open(self,  ws:  websocket) -> None:
        print("[INFO][ON_OPEN] Connexion établie avec le serveur Rosbridge")
        self.subscribe()

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

    def subscribe(self) -> None:
        if not self.ws or not self.ws.sock or not self.ws.sock.connected:
            print("[INFO][SUBSCRIBE] WebSocket n'est pas connecté. Tentative de reconnexion...")
            return
        
        for topic, msg_type in self.topic_to_subscribe.items():
            print(f"[INFO][SUBSCRIBE] Subscribing to: {topic} with type: {msg_type}")
            subscribe_message = {
                "op": "subscribe",
                "topic": topic,
                "type": msg_type
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

