import json
import time
import os

class Payload(object):
    def __init__(self,j):
        self.__dict__ = json.loads(j)


class Capture():
    def __init__(self,c):
        self.camera = c
        self.count = 0
    def snap(self,username):
        newpath = '/home/pi/Desktop/ohsnap/img/'+username
        if not os.path.exists(newpath):
            os.makedirs(newpath)
            
        self.camera.start_preview()
        time.sleep(5)
        self.camera.stop_preview()
        self.camera.capture('/home/pi/Desktop/ohsnap/img/'+username+'/%s.jpg'%self.count)
    def registration(self,user_name):
        self.camera.start_preview()
        time.sleep(5)
        self.camera.stop_preview()
        self.camera.capture('/home/pi/Desktop/ohsnap/img/'+user_name+'.jpg')

    def login(self):
        self.camera.start_preview()
        time.sleep(5)
        self.camera.stop_preview()
        self.camera.capture('/home/pi/Desktop/ohsnap/img/snap.jpg',quality=50)
