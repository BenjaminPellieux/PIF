
## Description
This project contains the web server part of the PIF WALLE system, designed to handle web-based interactions with the WALLE platform. It integrates functionalities for managing video streaming, WebSocket communication with ROS, and handling general HTTP requests.

## Features
- WebSocket communication via `client_rosbridge.py`
- Video streaming setup in `client_video.py`
- HTTP request handling in `handle_request.py`
- Utilities and configurations related to topics in `lib_topic.py`
- Core web server functionality in `code_serveur_pif.py`

## Requirements
- Python 3.6 or higher
- Flask
- OpenCV-Python (for video handling)
- Additional Python libraries: `flask`, `websocket-client`, `json`, `threading`



## Installation
1. Clone the repository:
2. Install required Python packages:

```py
pip install -r requirements.txt
```

## Configuration
Before running the server, ensure all configurations in `lib_topic.py` and other modules are set according to your system and network setup.

## Contributing
Contributions to the PIF WALLE Web Server are welcome. Please fork the repository and submit pull requests to the development branch.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
