# -*- coding: utf-8 -*-
"""
Created on Thu Jun 27 11:09:12 2019

@author: GELab
"""

import serial
import time
# "COM11" is the port that your Arduino board is connected.set it to port that your are using        
ser = serial.Serial("COM11", 9600,timeout= 5)


ser.write("Get_Position".encode('utf-8'))
ser.readline()

ser.write("POS_WithoutApp,200,-250,200".encode('utf-8'))
ser.readline()

ser.write("Get_Position".encode('utf-8'))
ser.readline()



ser.write("POS_WithoutApp,100,-350,200".encode('utf-8'))
ser.readline()


ser.write("POS_WithApp,150,-350,200,0".encode('utf-8'))
ser.readline()

ser.write("Hold,20".encode('utf-8'))
ser.readline()





ser.close()

