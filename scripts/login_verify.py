import requests
import picamera
import time
import json
import utils

def main():
    #send POST request to detect faces in database
    files ={'file':open('/home/pi/Desktop/ohsnap/img/login.jpg','rb')}
    #r= requests.post('http://104.199.127.227:5001/new_face/REX',files=files)
    r= requests.post('http://35.230.95.204:5001/detect_face',files=files)
    output = open("/home/pi/Desktop/ohsnap/test.txt","w")
    if(r.status_code != 200):
        output.write("f")
    else: 
        response = utils.Payload(r.text)
        if(response.face_found_in_image and response.picture_of != 'Unrecognized'): 
            output.write(response.picture_of)
        else:
            output.write("Unrecognized")
main()
