# How to Run the PIF WALLE Web Server Locally

## Overview
This guide will walk you through the steps needed to get your local instance of the PIF WALLE Web Server up and running on your computer.

## Steps

### 1. Setup the Environment
Make sure Python and all required packages are installed as mentioned in the README.md.

### 2. Clone the Repository
If you haven't already, clone the project repository:


### 3. Navigate to the Project Directory
Change into the project directory:



### 4. Start the Server
Run the main server script:

```sh
python3 code_serveur_pif.py
```

This will start the Flask server and other necessary services like the video streaming and WebSocket communication modules.

On your Lubuntu VM you have to start the rosbridge app 
```sh
roslaunch rosbridge_server rosbridge_websocket.launch port:=9090 ip:=10.8.0.3
```

#### 4.1 Start Local

Then to get the Jackal topic on your VM you'll have to use Jackal Gazebo simulation

```sh
roslaunch jackal_gazebo jackal_world.launch
```

### 4.2 Start on serveur

To Run the main server script on the ovh server you'll have to add the parameter ovh while starting code_server_pif.py :
```sh
python3 code_serveur_pif.py ovh 
```

You can make the programme un back ground by additing & at the end of the command line


### 5. Access the Web Interface
Open a web browser and go to:

http://localhost:5000

(replace `5000` with the actual port number used by your server if different)

## Troubleshooting
- **Server doesn't start:** Check the Python version and ensure all dependencies are installed.
- **WebSocket errors:** Ensure the WebSocket server address and ports in `client_rosbridge.py` are correct.
- **Video streaming issues:** Confirm that OpenCV is properly installed and the camera or video source is correctly configured in `client_video.py`.

## Further Assistance
For further help, please refer to the project's issue tracker or contact the development team.

