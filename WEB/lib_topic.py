
command_topic: dict ={
                    "F": {"linear" : {"x": 0.1}}, 
                    "B": {"linear": {"x": -0.1}}, 
                    "R": {"angular": {"z": -0.1}}, 
                    "L": {"angular": {"z": 0.1}}
                    }

commande_move: dict = {"linear": { 
                    "x": 0.0,
                    "y": 0.0,
                    "z": 0.0
                    },
                     "angular": {
                    "x": 0.0,
                    "y": 0.0,
                    "z": 0.0
                    }
                }

topic_type_dict: dict ={  "/odometry/filtered": "nav_msgs/Odometry",
                           "/navsat/fix" :  "sensor_msgs/NavSatFix"}
zone_topic: dict={"header": {
                            "seq": None,
                            "stamp":None,
                            "frame_id": None
                             },
                  "point": {
                            "x":0.0,
                            "y":0.0,
                            "z":0.0,
                            }
                  }


# command_topic: dict = {
#     "reset": {
#         "linear": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         },
#         "angular": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         }
#     },
#     "F": {
#         "linear": {
#             "x": 5.0,
#             "y": 0.0,
#             "z": 0.0
#         },
#         "angular": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         }
#     },
#     "B": {
#         "linear": {
#             "x": -1.0,
#             "y": 0.0,
#             "z": 0.0
#         },
#         "angular": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         }
#     },
#     "R": {
#         "linear": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         },
#         "angular": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": -1.0
#         }
#     },
#     "L": {
#         "linear": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         },
#         "angular": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 1.0
#         }
#     },  
#     "STOP": {
#         "linear": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         },
#         "angular": {
#             "x": 0.0,
#             "y": 0.0,
#             "z": 0.0
#         }
#     }
# }

