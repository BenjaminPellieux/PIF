from client_rosbridge import *
from lib_topic import *

def handle_points(data):

    print(f"[DEBUG]  data: {data=} {len(data)=})")
    area = {i:data[i] for i in range(len(data))}
    print(f"[DEBUG]  area: {area=} {len(area)=})")


def handle_command(data):
    ws_app.publish('/jackal_velocity_controller/cmd_vel', 'geometry_msgs/Twist', command_topic[data])
    print(f"[DEBUG] handle command \n Reciv command : {data=}\n Send topic: {command_topic[data]=}") 
#/cmd_vel geometry_msgs/Twist
def get_bridge_topic():
    print(f"[DEBUG] Get bridge topic") 


