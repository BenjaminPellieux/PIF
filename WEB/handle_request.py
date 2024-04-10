from client_rosbridge import *
from lib_topic import *
from datetime import datetime
current_speed: float = 5.0
cmd_continue: bool = False




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
            ros_client.publish('/pif/web/area/point', 'sensor_msgs/NavSatFix', message)
        except:
            print("[ERROR] WebSocket closed")

def change_speed(speed: str, ros_client: WebSocketApp):
    global current_speed
    if ros_client.topic_data:
        current_speed = int(speed)

    
def change_continue(status: str, ros_client: WebSocketApp):
    global cmd_continue
    if ros_client.topic_data:
        cmd_continue = bool(status)
        print(f"[DEBUG] {cmd_continue=}")
    
def handle_command(cmnd: str, ros_client: WebSocketApp):
    global current_speed
    global cmd_continue
     # Vérifiez si la clé est présente dans command_topic
    if cmnd in command_topic:
        command_changes: dict = command_topic[cmnd] 

        # Mise à jour des valeurs de 'linear' et 'angular' dans 'commande_move'
        for command_type, values in command_changes.items():
            for axis, value in values.items():
                commande_move[command_type][axis] = float(value) * current_speed
           
        print(f"[DEBUG] {commande_move=}")              
        try: 
            ros_client.publish('/jackal_velocity_controller/cmd_vel', 'geometry_msgs/Twist', commande_move)
        except:
            print("[ERROR] WebSocket closed")

        for command_type, values in commande_move.items():
            for axis, value in values.items():
                commande_move[command_type][axis] = 0.0
        
        print(f"[DEBUG] {commande_move=}")

