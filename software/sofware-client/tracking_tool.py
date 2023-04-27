import cv2 
import numpy as np 
from pyzbar.pyzbar import decode 
import time 

cap = cv2.VideoCapture(-1)
start_time = 0 
count = 0 
list_pos = []
list_pos_array = np.array([])
while True:
    count += 1 
    _, frame = cap.read()
    frame_draw = frame.copy()
    barcode = decode(frame)
    
    # for barcode in barcodes:
    if len(barcode):
        if len(barcode[0].polygon) != 4: 
            pass 
        else:
            p1_x = barcode[0].polygon[0].x
            p1_y = barcode[0].polygon[0].y
            
            p2_x = barcode[0].polygon[1].x 
            p2_y = barcode[0].polygon[1].y

            p3_x = barcode[0].polygon[2].x 
            p3_y = barcode[0].polygon[2].y

            p4_x = barcode[0].polygon[3].x 
            p4_y = barcode[0].polygon[3].y
    # barcodeData = barcode.data.decode("utf-8")
    # (rv, points, straight_qrcode) = cv2.QRCodeDetector().detectAndDecode(frame)

    
            G_y = round((p2_y + p4_y) / 2.0)
            G_x = round((p2_x + p4_x) / 2.0)
            list_pos.append((G_x, G_y))
    if count == 1:
        count = 0 
        list_pos_array = np.array(list_pos, np.int32)
        list_pos_array = list_pos_array.reshape((-1,1,2))
        
    cv2.polylines(frame_draw, list_pos_array, True, (0, 0, 255), 5)
        

    key = cv2.waitKey(1)
    if key == ord("q"):
        print(list_pos)
        break
    cv2.imshow("Streaming", frame) # chỉ cần comment dòng này thì sẽ không show UI 
    cv2.imshow("draw", frame_draw)

cv2.destroyAllWindows()
cap.release()
