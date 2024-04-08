from client_rosbridge import *
from lib_topic import *
from datetime import datetime
current_speed: float = 0.5


def handle_zone(data: list, ros_client: WebSocketApp):
    area: dict = {i:data[0][i] for i in range(len(data[0]))}
    print(f"[DEBUG]  area: {area=} {len(area)=}")
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

        print(f"[DEBUG] message_point :{i} {message=}")
        try: 
            ros_client.publish('/Area/Point', 'sensor_msgs/NavSatFix', message)
        except:
            print("[ERROR] WebSocket closed")

def change_speed(speed: str, ros_client: WebSocketApp):
    global current_speed
    if ros_client.topic_data:
        current_speed = int(speed)

def change_mode(mode: str, ros_client: websocket):
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
        ros_client.publish('/pif/web/mode/status', "std_msgs/Bool" , message)
    except:
        print("[ERROR] WebSocket closed")

def continue_mode(continue: str, ros_client: WebSocketApp):
    global continue_m
    if continue == "1":
        message: dict = {
            "data": True
        }
    else:
        message: dict = {
            "data": False
            }
    print(f"[DEBUG] message_point : {message=}")
    try: 
        ros_client.publish('/pif/web/mode/continue', "std_msgs/Bool" , message)
    except:
        print("[ERROR] WebSocket closed")        


def handle_command(cmnd: str, ros_client: WebSocketApp):
    global current_speed
     # Vérifiez si la clé est présente dans command_topic
    if cmnd in command_topic:
        command_changes: dict = command_topic[cmnd]

        # Mise à jour des valeurs de 'linear' et 'angular' dans 'commande_move'
        for command_type, values in command_changes.items():
            for axis, value in values.items():
                commande_move[command_type][axis] = value * current_speed
            if ros_client.orient and command_type != "angular":
                commande_move["angular"]["z"] +=  ros_client.orient["z"]
    try: 
        ros_client.publish('/jackal_velocity_controller/cmd_vel', 'geometry_msgs/Twist', command_changes)
    except:
        print("[ERROR] WebSocket closed")

