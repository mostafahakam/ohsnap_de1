import requests
import picamera
import time
import json
import utils
import filters
from PIL import ImageEnhance,Image,ImageChops

camera = picamera.PiCamera()

#receive commands from de1 telling me to take a picture of the user
cap = utils.Capture(camera)
cap.login()

#send POST request to detect faces in database
files ={'file':open('/home/pi/Desktop/Login.jpg','rb')}
#r= requests.post('http://104.199.127.227:5001/new_face/REX',files=files)
r= requests.post('http://35.230.95.204:5001/detect_face',files=files)


#receive the feedback from the server
if(r.status_code != 200):
    print("Unacceptable requests with status_code " ,r.status_code)
else: 
    print(r.text)
    response = utils.Payload(r.text)
    if(response.face_found_in_image and response.picture_of != 'Unrecognized'): 
        print('Hello! '+response.picture_of)
        #Now send signal to de1 confirming the user and wait for furthur commands
        img = Image.open('Login.jpg')
        filters = filters.Filters(img)
        filter_num = int(input('which filter do you want? input (1)Auto Enhance (2)Black&White (3)Cold temperature (4)Warm temperature (5)High saturation (Any num)See every filter\n'))
        
        if(filter_num == 1):
            filters.Enhance()
            files ={'file':open('/home/pi/Desktop/1.jpg','rb')}
            r= requests.post('http://35.230.95.204:5001/detect_face',files=files)
        elif(filter_num == 2):
            filters.BW()
            files ={'file':open('/home/pi/Desktop/2.jpg','rb')}
            r= requests.post('http://35.230.95.204:5001/detect_face',files=files)
        elif(filter_num == 3):
            filters.custom1()
            files ={'file':open('/home/pi/Desktop/3.jpg','rb')}
            r= requests.post('http://35.230.95.204:5001/detect_face',files=files)
        elif(filter_num == 4):
            filters.custom2()
            files ={'file':open('/home/pi/Desktop/4.jpg','rb')}
            r= requests.post('http://35.230.95.204:5001/detect_face',files=files)
        elif(filter_num == 5):
            filters.satura()
            files ={'file':open('/home/pi/Desktop/5.jpg','rb')}
            r= requests.post('http://35.230.95.204:5001/detect_face',files=files)
        else:
            filters.Enhance()
            filters.BW()
            filters.custom1()
            filters.custom2()
            filters.satura()
    else:
        print("not recognized")
        #Now send signal to de1 telling that this is a new user/not recognized
