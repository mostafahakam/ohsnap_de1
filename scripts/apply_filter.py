import requests
import picamera
import time
import json
import utils
import filters
import sys
from PIL import ImageEnhance,Image,ImageChops

filter_num_str = sys.argv[1]
filter_num = int(filter_num_str)
img = Image.open('/home/pi/Desktop/ohsnap/img/snap.jpg')
filters = filters.Filters(img)

if(filter_num == 1):
    filters.Enhance()
elif(filter_num == 2):
    filters.BW()
elif(filter_num == 3):
    filters.custom1()
elif(filter_num == 4):
    filters.custom2()
elif(filter_num == 5):
    filters.satura()
else:
    filters.Enhance()
    filters.BW()
    filters.custom1()
    filters.custom2()
    filters.satura()
