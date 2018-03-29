import requests
import picamera
import time
import json
import utils


def main():
    camera = picamera.PiCamera()

    #receive commands from de1 telling me to take a picture of the user
    cap = utils.Capture(camera)
    cap.login()

main()
