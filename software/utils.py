xo = 240 
yo = 187
wo = 180 
ho = 180

x_g = 0
y_g = 0
w_g = 639 
h_g = 479

##### 9 regions  of interest ####
w_s = 213 
h_s = 159
# region 1 
x1 = 0 
y1 = 0 
# region 2 
x2 = 213 
y2 = 0 
# region 3 
x3 = 426 
y3 = 0 
# region 4 
x4 = 0 
y4 = 159 
# region 5 
x5 = 213 
y5 = 159 
# region 6 
x6 = 426 
y6 = 159 
# region 7 
x7 = 0 
y7 = 318 
# region 8 
x8 = 213 
y8 = 318 
# region 9
x9 = 426 
y9 = 318 

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

def CheckCase(p1_x, p1_y, p2_x, p2_y, p3_x, p3_y, p4_x, p4_y):
    if (p1_x >= x1 and p1_y <= y1 + h_s) and (p2_x <= x1 + w_s and p2_y <= y1 + h_s) and (p3_x <= x1 + w_s and p3_y >= y1) and (p4_x >= x1 and p4_y >= y1): 
        return pcTOPLEFT 
    elif (p1_x >= x2 and p1_y <= y2 + h_s) and (p2_x <= x2 + w_s and p2_y <= y2 + h_s) and (p3_x <= x2 + w_s and p3_y >= y2) and (p4_x >= x2 and p4_y >= y2):
        return pcHEAD 
    elif (p1_x >= x3 and p1_y <= y3 + h_s) and (p2_x <= x3 + w_s and p2_y <= y3 + h_s) and (p3_x <= x3 + w_s and p3_y >= y3) and (p4_x >= x3 and p4_y >= y3):
        return pcTOPRIGHT 
    elif (p1_x >= x4 and p1_y <= y4 + h_s) and (p2_x <= x4 + w_s and p2_y <= y4 + h_s) and (p3_x <= x4 + w_s and p3_y >= y4) and (p4_x >= x4 and p4_y >= y4):
        return pcMIDLEFT
    elif (p1_x >= x5 and p1_y <= y5 + h_s) and (p2_x <= x5 + w_s and p2_y <= y5 + h_s) and (p3_x <= x5 + w_s and p3_y >= y5) and (p4_x >= x5 and p4_y >= y5): 
        return pRUN 
    elif (p1_x >= x6 and p1_y <= y6 + h_s) and (p2_x <= x6 + w_s and p2_y <= y6 + h_s) and (p3_x <= x6 + w_s and p3_y >= y6) and (p4_x >= x6 and p4_y >= y6): 
        return pcMIDRIGHT 
    elif (p1_x >= x7 and p1_y <= y7 + h_s) and (p2_x <= x7 + w_s and p2_y <= y7 + h_s) and (p3_x <= x7 + w_s and p3_y >= y7) and (p4_x >= x7 and p4_y >= y7): 
        return pcBOTTOMLEFT 
    elif (p1_x >= x8 and p1_y <= y8 + h_s) and (p2_x <= x8 + w_s and p2_y <= y8 + h_s) and (p3_x <= x8 + w_s and p3_y >= y8) and (p4_x >= x8 and p4_y >= y8): 
        return pcBACK 
    elif (p1_x >= x9 and p1_y <= y9 + h_s) and (p2_x <= x9 + w_s and p2_y <= y9 + h_s) and (p3_x <= x9 + w_s and p3_y >= y9) and (p4_x >= x9 and p4_y >= y9): 
        return pcBOTTOMRIGHT



    
    


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