from flask import Flask, render_template, jsonify, request
import json
from handle_request import *
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



@app.route('/get_topic_value', methods=['POST'])
def get_topic_value():
    data = request.json
    topic = data['topic']
    ws_app.subscribe(topic, topic_type_dict[topic])
    print(f"[INFO][UPDATE_TOPIC] topic: {topic} type: {topic_type_dict[topic]} Data {True if ws_app.topic_data.get(topic) else False}")
    if ws_app.topic_data.get(topic):
        return jsonify(ws_app.topic_data.get(topic))
    return jsonify("ERROR")

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
    app.run(host='localhost', port=8080, ssl_context=('cert.pem', 'key.pem'))
