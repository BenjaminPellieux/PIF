from flask import Flask, render_template, jsonify, request, send_file
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
    handle_command(request.form["comd"], ros_client)
    return "200"

@app.route('/newspeed', methods=['POST'])
def new_speed():
    change_speed(request.form["speed"], ros_client)
    return "200"

@app.route('/command_status', methods=['POST'])
def commandStatus():
    try:
        ros_client.publish('/pif/web/controle', 'std_msgs/Bool', {"data":request.form["comd"]})
    except:
        print("[ERROR] WebSocket closed")
        return "400"
    return "200"

@app.route('/continue_status', methods=['POST'])
def continueStatus():
    try:
        ros_client.publish('/pif/web/controle', 'std_msgs/Bool', {"data":request.form["comd"]})
    except:
        print("[ERROR] WebSocket closed")
        return "400"
    return "200"


@app.route('/post_topic_value', methods=['POST'])
def get_topic_value():
    data = request.json
    topic = data['topic']
    print(f"[INFO][UPDATE_TOPIC] topic: {topic} type: {topic_type_dict[topic]} Data {True if ros_client.topic_data.get(topic) else False}")
    #    print(f"[ERROR][UPDATE_TOPIC] NO DATA FOUND ")
    if ros_client.topic_data.get(topic):
        return jsonify(ros_client.topic_data.get(topic))
    return jsonify("ERROR")

@app.route('/current_image')
def current_image():
    return send_file('tmp/PIF.jpg', mimetype='image/jpeg')


@app.route('/area', methods=['POST'])
def area():
    handle_zone(json.loads(request.form["points"]), ros_client)
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
        ros_client: WebSocketApp = WebSocketApp(config["ip_rasp"])
    except:
        video_stream: WebVideoApp = WebVideoApp()
        ros_client: WebSocketApp = WebSocketApp()

    ros_client.start()
    video_stream.start()
    app.run(host='localhost', port=8080, ssl_context=('key/cert.pem', 'key/key.pem'), debug=False)
    