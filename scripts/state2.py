import RPi.GPIO as GPIO
from time import sleep

count = 0
GPIO.setmode(GPIO.BCM)
GPIO.setup(20,GPIO.OUT)
GPIO.setup(21,GPIO.OUT)
GPIO.output(20,0)
GPIO.output(21,1)
