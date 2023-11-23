from flask import Flask, render_template, jsonify, request
import json
from handle_request import *
app = Flask(__name__, static_folder='static')




@app.route('/')
def index():
    return render_template("index.html")

@app.route('/vision')
def vision():
    return render_template("vision.html")

@app.route('/gps')
def gps():
    return render_template("gps.html")

@app.route('/controle')
def controle():
    return render_template("controle.html")

@app.route('/aspiration')
def aspiration():
    return render_template("aspiration.html")

@app.route('/configuration')
def config():
    return render_template("configuration.html")

@app.route('/bridge_test')
def bridge():
    return render_template("rosbridge.html")

@app.route('/endpoint', methods=['POST'])
def endpoint():
    data = request.json

    print(data)
    # Traiter ou stocker les données ici
    return "Données reçues"

@app.route('/command', methods=['POST'])
def command():
    handle_command(request.form["comd"])
    return "200"

@app.route('/newspeed', methods=['POST'])
def new_speed():
    change_speed(request.form["speed"])
    return "200"



@app.route('/get_topic_value', methods=['POST'])
def get_topic_value():
    data = request.json
    topic = data['topic']
    if ws_app.topic_data.get(topic):
        return jsonify(ws_app.topic_data.get(topic))
    return jsonify("ERROR")

@app.route('/area', methods=['POST'])
def area():
    handle_points(json.loads(request.form["points"]))
    return "200"

@app.route('/locate', methods=['POST'])
def locate():
    data = (request.form["lat"], request.form["lon"], request.form["acc"]) 
    print(f"[DEBUG] location : {request.form=}") 
    print(f"[DEBUG] location : {data=}")
    return "200"
    


if __name__ == '__main__':
    app.run(host='localhost', port=8080)
