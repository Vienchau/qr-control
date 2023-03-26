from math import sqrt, atan2
from math import pi 


pNONE = 0
pcTOPLEFT = 1
pcTOPRIGHT = 2
pcBACK = 3
pcHEAD = 4
pcMIDLEFT = 5 
pcMIDRIGHT = 6
pcBOTTOMLEFT = 7
pcBOTTOMRIGHT = 8

pRUN = 9


def ComputeDistance(p2_x, p2_y, p4_x, p4_y, T_x, T_y):
    G_x = (p2_x + p4_x) / 2.0
    G_y = (p2_y + p4_y) / 2.0
    d = sqrt((T_x - G_x) ** 2 + (T_y - G_y) ** 2)
    return d 

def ComputeAngle(p2_x, p2_y, p4_x, p4_y, T_x, T_y):
    G_x = (p2_x + p4_x) / 2.0
    G_y = (p2_y + p4_y) / 2.0
    
    y = T_x - G_x 
    x = T_y - G_y 
    angle = atan2(y, x) # radian 
    # convert radian to degree 
    angle = angle * 180 / pi
    return angle 

def FixLength(value):
    if len(str(value)) == 1:
        return "000" + str(value)
    elif len(str(value)) == 2:
        return "00" + str(value)
    elif len(str(value)) == 3:
        return "0" + str(value)
    else: 
        return str(value)    


def FormatData(Pos, Vel, Acc, Dir1, Dir2):
    PosStr = FixLength(Pos)
    VelStr = FixLength(Vel)
    AccStr = FixLength(Acc)
    Dir1Str = str(Dir1)
    Dir2Str = str(Dir2)
    result = "{},{},{},{},{}".format(PosStr, VelStr, AccStr, Dir1Str, Dir2Str)
    return result