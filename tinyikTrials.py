

import tinyik
import numpy as np
np.set_printoptions(suppress=True)
arm = tinyik.Actuator(['z',[0,0,60],'x', [0, 0., 120.], 'x', [0., 0., 120.],'x',[0.,0.,180]])


## 90-theta



def convertAnglesToBraccio(angles):
    
    ##base, shoulder,arm,wrist
    
    [ang1,ang2,ang3,ang4] = angles
    
    newAngs = [90- ang for ang in angles]
    
    
    
    
    
    
    return newAngs


def convertAnglesFromBraccio(angles):
    
    ##base, shoulder,arm,wrist
    
    [ang1,ang2,ang3,ang4] = angles
    
    newAngs = [90 - ang for ang in angles]
    

    return newAngs




def getPosition(braccioAngles):
    
    angles = convertAnglesFromBraccio(braccioAngles)
    arm.angles = np.deg2rad(angles)
    
    endEffectorPos = arm.ee
    
    
    return endEffectorPos


anglesForLib = convertAnglesFromBraccio([0,74.30,68,3.6])
arm.angles = np.deg2rad([0]+anglesForLib[1:])
arm.ee


