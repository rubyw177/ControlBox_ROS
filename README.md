# ControlBox_ROS

## Overview
This project implements a **ROS (Robot Operating System) based control system** that connects an **Arduino-powered Control Box** for a **Remotely Operated Vehicle (ROV)** to a **PC via LAN**. The system uses **ROS messages** to transmit and receive control commands.

## Features
- **ROS Integration**: Uses ROS topics to communicate between the PC and the Control Box.
- **Custom Message Type**: Defines a `Controlbox.msg` for structured communication.
- **Arduino Control**: Implements firmware to interact with physical switches and actuators.
- **Subscriber Node**: Listens for commands from the control box and processes inputs.

## Project Structure
```
📂 project_root/
├── 📜 Controlbox.h          # Header file for Control Box commands
├── 📜 Controlbox.msg        # ROS message definition
├── 📜 controlbox_indicator.ino  # Arduino firmware
├── 📜 controlbox_listener.py    # ROS subscriber node
└── 📝 README.md             # Project documentation
```

## Dependencies
Ensure that you have the following installed:
```bash
sudo apt update && sudo apt install ros-noetic-ros-base
pip install rospy
```

## Usage
### 1. Setup the ROS Environment
```bash
source /opt/ros/noetic/setup.bash
```

### 2. Define the ROS Message Type
Before running the system, the **custom message type** must be compiled:
```bash
cd ~/catkin_ws
catkin_make
source devel/setup.bash
```

### 3. Launch the Listener Node
Run the ROS node that listens for control box commands:
```bash
rosrun controlbox controlbox_listener.py
```

### 4. Expected Output
When receiving data, the `controlbox_listener.py` script will print:
```
Key: A
Switch State: True
```
Where:
- **Key**: ASCII representation of the received keypress.
- **Switch State**: Boolean indicating whether the switch is active.

### 5. Upload Arduino Firmware
The **controlbox_indicator.ino** script must be uploaded to the **Arduino** to handle LED indicators and switch interactions.

## Implementation Details
### Controlbox.msg
Defines the message format for communication:
```text
char key    # Key input from control box
bool state  # On/Off switch state
```

### controlbox_listener.py
ROS node that listens for incoming messages:
```python
rospy.init_node("cb_listener", anonymous=True)
rospy.Subscriber("controlbox_cmd", Controlbox, callback)
rospy.spin()
```
