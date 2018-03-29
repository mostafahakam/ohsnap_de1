import requests
import picamera
import time
import utils
import sys

username = sys.argv[1]
camera = picamera.PiCamera()

#receive commands from de1 telling me to take a picture of the user
cap = utils.Capture(camera)
print("Let's remember your face now!")
time.sleep(2)
cap.registration(username)

files ={'file':open('/home/pi/Desktop/ohsnap/img/' + username + '.jpg','rb')}


r= requests.post('http://104.199.127.227:5001/new_face/' + user_name,files=files)

if(r.status_code != 200):
    print("Unacceptable requests with status_code " ,r.status_code)
else:
    print("The server has already saved your face!")
