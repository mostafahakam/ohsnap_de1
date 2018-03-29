import json
import time
import os
import datetime

class Payload(object):
    def __init__(self,j):
        self.__dict__ = json.loads(j)


class Capture():
    def __init__(self,c):
        self.camera = c
    def snap(self,username):
        newpath = '/home/pi/Desktop/ohsnap/img/'+username
        if not os.path.exists(newpath):
            os.makedirs(newpath)
            
        self.camera.start_preview()
        time.sleep(5)
        self.camera.stop_preview()
        date = datetime.datetime.now().strftime('%b-%d-%I%M%p-%G')
        self.camera.capture('/home/pi/Desktop/ohsnap/img/'+username+'/'+'%s.jpg'%date)
        output = open("/home/pi/Desktop/ohsnap/img/"+username+"/pnames.txt","a")
        output.write(date + '\n')
    def registration(self,user_name):
        self.camera.start_preview()
        time.sleep(5)
        self.camera.stop_preview()
        self.camera.capture('/home/pi/Desktop/ohsnap/img/'+user_name+'.jpg')

    def login(self):
        self.camera.start_preview()
        time.sleep(5)
        self.camera.stop_preview()
        self.camera.capture('/home/pi/Desktop/ohsnap/img/login.jpg')
