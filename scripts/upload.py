import requests
import picamera
import time
import json
import utils
import sys


photo_to_upload = sys.argv[1]
#send POST request to detect faces in database
files ={'file':open('/home/pi/Desktop/ohsnap/'+photo_to_upload,'rb')}
#r= requests.post('http://104.199.127.227:5001/new_face/REX',files=files)
r= requests.post('http://35.230.95.204:5001/upload_photo',files=files)

output = open("/home/pi/Desktop/ohsnap/output.txt","w")
if(r.status_code != 200):
    output.write("f")

