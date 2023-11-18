
def handle_points(data):

    print(f"[DEBUG]  data: {data=} {len(data)=})")
    area = {i:data[i] for i in range(len(data))}
    print(f"[DEBUG]  area: {area=} {len(area)=})")


def handle_command(data):
    print(f"[DEBUG] Reciv command : {data=}") 


def get_bridge_topic():
    print(f"[DEBUG] Get bridge topic") 
