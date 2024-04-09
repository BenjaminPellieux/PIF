from flask import Flask, render_template, jsonify, request, send_file
import json
from sys import argv
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
    change_continue(request.form["comd"], ros_client)
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
    try:
        return send_file('tmp/PIF.jpg', mimetype='image/jpeg')
    except:
        return "ERROR"

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
    


def load_config(environment=None):
    """Charge un fichier de configuration en fonction de l'environnement spécifié."""
    if environment == "ovh":
        config_path = "config/serv_config.json"  # Chemin vers le fichier de configuration pour OVH
    else:
        config_path = "config/config.json"  # Chemin par défaut

    try:
        with open(config_path, 'r') as file:
            return json.load(file)
    except FileNotFoundError:
        print(f"Erreur : Le fichier {config_path} n'a pas été trouvé.")
        exit(1)
    except json.JSONDecodeError:
        print(f"Erreur : Le fichier {config_path} n'est pas un JSON valide.")
        exit(1)


if __name__ == '__main__':
    # Vérifie si un argument a été passé et utilise cet argument comme indication de l'environnement
    environment = argv[1] if len(argv) > 1 else None
    config = load_config(environment)

    try:
        video_stream = WebVideoApp(config["ip_lan"])
        ros_client = WebSocketApp(config["ip_rasp"])
    except KeyError as e:
        print(f"Erreur de configuration : clé {str(e)} manquante.")
        exit(1)

    ros_client.start()
    video_stream.start()

    try:
        app.run(host=config.get('host', 'localhost'),
                port=config.get('port', 8080),
                ssl_context=('key/cert.pem', 'key/key.pem'),
                debug=False)
    except Exception as e:
        print(f"Erreur lors du lancement du serveur : {str(e)}")
        exit(1)