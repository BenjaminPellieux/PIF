from client_rosbridge import *
from lib_topic import *
from datetime import datetime
current_speed: float = 0.5


def handle_zone(data: list):
    area: dict = {i:data[0][i] for i in range(len(data[0]))}
    print(f"[DEBUG]  area: {area=} {len(area)=})")
    topic_type: str = "sensor_msgs/NavSatFix"
    for i, point_info in area.items():
        message: dict = {
                "header": {
                            "seq": i,  # Sequence number (i)
                            "stamp": datetime.timestamp(datetime.now()),  # Time stamp
                            "frame_id": f"P{i}"  # ID of the point
                          },
                "latitude": point_info['lat'], # latitude
                "longitude": point_info['lng'] # longitude
                }
                #"point": {
                #    "x": point_info['lat'],  # latitude
                #    "y": point_info['lng'],  # longitude
                #    "z": 0.0,  # Unused
                #     }
                #}
        print(f"[DEBUG] message_point :{i} {message=}")
        try: 
            ws_app.publish('/Area/Point', 'sensor_msgs/NavSatFix', message)
        except:
            print("[ERROR] WebSocket closed")

def change_speed(speed: str):
    global current_speed
    if ws_app.topic_data:
        current_speed = int(speed)

def change_mode(mode: str):
    topic_type: str = "std_msgs/Bool"
    if mode == "1":
    	message: dict = {
    		"data": True
    		}
    else:
    	message: dict = {
    		"data": False
    		}
    print(f"[DEBUG] message_point : {message=}")
    try: 
        ws_app.publish('/Area/Point', topic_type, message)
    except:
        print("[ERROR] WebSocket closed")


def handle_command(cmnd: str):
    global current_speed
     # Vérifiez si la clé est présente dans command_topic
    if cmnd in command_topic:
        command_changes: dict = command_topic[cmnd]

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

