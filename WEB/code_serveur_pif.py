from flask import Flask, render_template, after_this_request, request

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


@app.route('/command', methods=['POST'])
def command():
    #response.headers['Access-Control-Allow-Origin'] = '*'
    #input_json = request.get_json(force=True) 
    com = request.form["javascript_data"] 
    print(f"[DEBUG] Reciv command : {com=}") 
    return "200"


@app.route('/locate', methods=['POST'])
def locate():
    data = (request.form["lat"], request.form["lon"], request.form["acc"]) 
    print(f"[DEBUG] location : {request.form=}") 
    print(f"[DEBUG] location : {data=}")
    return "200"
    


if __name__ == '__main__':
    app.run(host='localhost', port=8080)
