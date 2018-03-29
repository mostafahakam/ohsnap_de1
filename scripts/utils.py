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
    def routine(self,folder):
        self.camera.start_preview()
        time.sleep(5)
        self.camera.stop_preview()
        
        newpath = '/home/pi/Desktop/'+folder
        if not os.path.exists(newpath):
            os.makedirs(newpath)
            
        self.camera.capture('/home/pi/Desktop/'+folder+'/'+'user%d.jpg'%self.count)
        self.count += 1
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
    
    
