from client_rosbridge import *
from lib_topic import *

current_speed = 5


def handle_points(data):

    print(f"[DEBUG]  data: {data=} {len(data)=})")
    area = {i:data[i] for i in range(len(data))}
    print(f"[DEBUG]  area: {area=} {len(area)=})")

def change_speed(speed):
    global current_speed
    if ws_app.topic_data:
        current_speed = int(speed)

def handle_command(cmnd):

     # Vérifiez si la clé est présente dans command_topic
    if cmnd in command_topic:
        command_changes = command_topic[cmnd]

        # Mise à jour des valeurs de 'linear' et 'angular' dans 'commande_move'
        for command_type, values in command_changes.items():
            for axis, value in values.items():
                commande_move[command_type][axis] = value * current_speed
            if ws_app.orient and command_type != "angular":
                commande_move["angular"]["z"] +=  ws_app.orient["z"]
    try: 
        ws_app.publish('/jackal_velocity_controller/cmd_vel', 'geometry_msgs/Twist', command_changes)
    except:
        print("[ERROR] WebSocket closed")
#/cmd_vel geometry_msgs/Twist
def get_bridge_topic():
    print(f"[DEBUG] Get bridge topic") 


