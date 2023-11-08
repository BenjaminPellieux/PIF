from flask import Flask, render_template, after_this_request, request
import json
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


@app.route('/command', methods=['POST'])
def command(): 
    com = request.form["javascript_data"] 
    print(f"[DEBUG] Reciv command : {com=}") 
    return "200"


@app.route('/area', methods=['POST'])
def area():
    data = json.loads(request.form["points"])
    area = {i:data[i] for i in range(len(data))}
    print(f"[DEBUG] location : {area=}")
    return "200"

@app.route('/locate', methods=['POST'])
def locate():
    data = (request.form["lat"], request.form["lon"], request.form["acc"]) 
    print(f"[DEBUG] location : {request.form=}") 
    print(f"[DEBUG] location : {data=}")
    return "200"
    


if __name__ == '__main__':
    app.run(host='localhost', port=8080)
