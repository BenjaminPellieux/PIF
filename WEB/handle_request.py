from client_rosbridge import *
from lib_topic import *
from datetime import datetime
current_speed = 5


def handle_zone(data):
    area: dict = {i:data[0][i] for i in range(len(data[0]))}
    print(f"[DEBUG]  area: {area=} {len(area)=})")
    topic_type: str = "geometry_msgs/PointStamped"
    for i, point_info in area.items():
        message: dict = {
                "header": {
                            "seq": i,  # Sequence number (i)
                            "stamp": datetime.timestamp(datetime.now()),  # Time stamp
                            "frame_id": f"P{i}"  # ID of the point
                          },
                "point": {
                    "x": point_info['lat'],  # latitude
                    "y": point_info['lng'],  # longitude
                    "z": 0.0,  # Unused

                     }
                }
        print(f"[DEBUG] message_point :{i} {message=}")
    try: 
        ws_app.publish('/Area/Points', 'geometry_msgs/PointStamped', command_changes)
    except:
        print("[ERROR] WebSocket closed")

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


def get_bridge_topic():
    print(f"[DEBUG] Get bridge topic") 


