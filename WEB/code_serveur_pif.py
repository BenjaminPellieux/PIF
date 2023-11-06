from flask import Flask, render_template

app = Flask(__name__, static_folder='static')

@app.route('/')
def test():
    return render_template("test.html")

if __name__ == '__main__':
    app.run(host='localhost', port=8080)
