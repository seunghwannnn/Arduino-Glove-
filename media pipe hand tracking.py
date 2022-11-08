import serial                                 
import time
import cv2
import mediapipe as mp
import math
from ctypes import cast,POINTER



py_serial = serial.Serial(  
    port='COM9',               # COM9으로 PORT 설정
    baudrate=9600,             # 통신을 위한 Baudrate 9600으로 설정
)


cap = cv2.VideoCapture(0)      

mpHands = mp.solutions.hands
my_hands = mpHands.Hands()
mpDraw = mp.solutions.drawing_utils

def dist(x1,y1,x2,y2):
    return math.sqrt(math.pow(x1 - x2,2)) + math.sqrt(math.pow(y1 - y2,2))    
compareIndex = [[9,4],[6,8],[10,12],[14,16],[18,20]]                          
open = [False,False,False,False,False] 

 
gesture = [
            [False,False,False,False,False,"S"],
            [True,False,False,False,False,"L"],
            [False,True,True,True,True,"R"],
            [False,True,False,False,False,"G"],
            [True,True,True,True,True,"B"]
          ]


while True:
    
    success,img = cap.read()
    h,w,c = img.shape
    imgRGB = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
    results = my_hands.process(imgRGB)
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            for i in range(0,5):
                open[i] = dist(handLms.landmark[0].x,handLms.landmark[0].y,handLms.landmark[compareIndex[i][0]].x,handLms.landmark[compareIndex[i][0]].y) < dist(handLms.landmark[0].x,handLms.landmark[0].y,handLms.landmark[compareIndex[i][1]].x,handLms.landmark[compareIndex[i][1]].y)
            
            text_x = (handLms.landmark[0].x * w)
            text_y = (handLms.landmark[0].y * h)
            if open[3] == False:
                curdist = -dist(handLms.landmark[4].x,handLms.landmark[4].y,handLms.landmark[8].x,handLms.landmark[8].y) / (dist(handLms.landmark[2].x,handLms.landmark[2].y,handLms.landmark[5].x,handLms.landmark[5].y) * 2)
                curdist = curdist * 100
                curdist = -96 - curdist
                curdist = min(0,curdist)
        
        
               
            for i in range(0,len(gesture)):
                flag = True
                for j in range(0,5):
                    if(gesture[i][j] != open[j]):
                        flag = False
                if(flag == True):
                    py_serial.write(gesture[i][5].encode())
                    print(gesture[i][5])
                    cv2.putText(img,gesture[i][5],(round(text_x) - 50,round(text_y) - 250),cv2.FONT_HERSHEY_PLAIN,4,(0,0,0),4)

                     
            mpDraw.draw_landmarks(img,handLms,mpHands.HAND_CONNECTIONS)
    
   
    cv2.imshow("HandTracking",img)
    cv2.waitKey(1)
    

  
    
