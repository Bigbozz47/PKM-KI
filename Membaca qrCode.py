import cv2 as cv
import numpy as np
from pyzbar.pyzbar import decode

cap = cv.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)

while True:
    succer, img1 = cap.read()
    for barcode in decode(img1):
        myData = barcode.data.decode('utf-8')
        print(myData)
        points = np.array([barcode.polygon],np.int32)
        points = points.reshape((-1,1,2))
        cv.polylines(img1, [points],True,(225,0,0),5)
        points2 = barcode.rect
        cv.putText(img1, myData,(points2[0],points2[1]),cv.FONT_HERSHEY_SIMPLEX,0.9,(255,0,255),2)
    
    cv.imshow("Result", img1)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break


