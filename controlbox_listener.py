#!/usr/bin/env python3
import rospy
from pesan_pkg.msg import Controlbox

def callback(data):
    print("Key:", chr(data.key))  # convert ascii value to char value
    print("Switch State:", data.state)  # state is in bool

def listener():
    rospy.init_node("cb_listener", anonymous=True)

    rospy.Subscriber("controlbox_cmd", Controlbox, callback)

    rospy.spin()

if __name__ == "__main__":
    listener()
