from flask import Flask, render_template, jsonify, request, Response, send_file
import json
from handle_request import *
from client_video import *

# IP_RASP = "192.168.131.1"
IP_RASP = "10.8.0.3"
PORT = "9090"
# PORT = "11311"


app = Flask(__name__, static_folder='static')




@app.route('/')
def index():
    return render_template("index.html")

@app.route('/controle')
def controle():
    return render_template("controle.html")

@app.route('/configuration')
def config():
    return render_template("configuration.html")

@app.route('/command', methods=['POST'])
def command():
    handle_command(request.form["comd"])
    return "200"

@app.route('/newspeed', methods=['POST'])
def new_speed():
    change_speed(request.form["speed"])
    return "200"
    
@app.route('/mode', methods=['POST'])
def mode():
    change_mode(request.form["mode"])
    return "200"

@app.route('/commandstatus', methods=['POST'])
def commandStatus():
    try: 
        ws_app.publish('/Controle/Status', 'std_msgs/Bool', request.form["comd"])
    except:
            print("[ERROR] WebSocket closed")
    return "200"



@app.route('/get_topic_value', methods=['GET'])
def get_topic_value():
    data = request.json
    topic = data['topic']
    ws_app.subscribe(topic, topic_type_dict[topic])
    print(f"[INFO][UPDATE_TOPIC] topic: {topic} type: {topic_type_dict[topic]} Data {True if ws_app.topic_data.get(topic) else False}")
    if ws_app.topic_data.get(topic):
        return jsonify(ws_app.topic_data.get(topic))
    return jsonify("ERROR")

@app.route('/current_image')
def current_image():

    print(f"[DEBUG] /current_image ")
    return send_file('tmp/PIF.jpg', mimetype='image/jpeg')


@app.route('/area', methods=['POST'])
def area():
    handle_zone(json.loads(request.form["points"]))
    return "200"

@app.route('/locate', methods=['POST'])
def locate():
    data = (request.form["lat"], request.form["lon"], request.form["acc"]) 
    print(f"[DEBUG] location : {request.form=}") 
    print(f"[DEBUG] location : {data=}")
    return "200"
    


if __name__ == '__main__':
    
    try:
        config = json.load(open("config/config.json"))
        video_stream: WebVideoApp = WebVideoApp(config["ip_rasp"])
        ws_app: WebSocketApp = WebSocketApp(config["ip_rasp"])
    except:
        video_stream: WebVideoApp = WebVideoApp()
        ws_app: WebSocketApp = WebSocketApp()

    ws_app.start()
    video_stream.start()
    app.run(host='localhost', port=8080, ssl_context=('key/cert.pem', 'key/key.pem'))
    