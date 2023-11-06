from flask import Flask, render_template

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


if __name__ == '__main__':
    app.run(host='localhost', port=8080)
