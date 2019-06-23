# -*- coding: utf-8 -*-
"""
Created on Sat Oct 27 00:22:07 2018

@author: bhaik
"""

#improve code for color detection

from imutils.video import VideoStream
from pyzbar import pyzbar
import argparse
#import datetime
import imutils
import time
#import serial
import cv2
import numpy as np

#def barcode():
    
#    Arduinouno_Serial = serial.Serial('COM7',9600)
    
#    vs = VideoStream(0).start()
#    time.sleep(2.0)

#    frame = vs.read()
#    frame= imutils.resize(frame, width = 600)
    
    
#    for barcode in barcodes:
#         (x, y, w, h) = barcode.rect
#         cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
         
#         barcodeData = barcode.data.decode("utf-8")
#         print("barcodes: ", barcodeData)
         
#         for i in range(1):
#             Arduinouno_Serial.write('0'.encode())
#             time.sleep(2.0)
         
#         if barcodeData not in found:
#             csv.write("{},{}\n".format(datetime.datetime.now(), barcodeData))
#             csv.flush()
#             found.add(barcodeData)


def main():
    
#    Arduinouno_Serial = serial.Serial('COM7',9600)
#    print (Arduinouno_Serial.readline())
    
    #ap = argparse.ArgumentParser()
    #ap.add_argument("-o","--output",type=str,default="barcodes2.csv",help = "path to output csv file containing barcodes")
    
    #args = vars(ap.parse_args())
    
    print("[INFO] starting video stream...")
    
    #vs = VideoStream(0).start()
    
    
    vs = VideoStream(0).start()
    time.sleep(2.0)
    
    frame = vs.read()
    
    #csv = open(args["output"], "w")
    #found = set()
    
    print("[INFO] starting video stream...")
    
    
    #h = 480
    #w = 640
    x1=300
    x2=320
    y1=240
    y2=260
    #cap.set(3,w)
    #cap.set(4,h)
    #if cap.isOpened():
    #    ret, frame = cap.read()
    #else:
    #    ret = False
    
    
        
    while True:
        frame = vs.read()
        frame_org = frame
        frame = imutils.resize(frame, width = 600)
        #scale_percent = 60
        #width = int(frame.shape[1] * scale_percent / 100)
        #height = int(frame.shape[0] * scale_percent / 100)
        #dim = (600, 400)
        #frame = cv2.resize(frame, dim, interpolation = cv2.INTER_AREA )
        
        barcodes = pyzbar.decode(frame)
        
        for barcode in barcodes:
            (x, y, w, h) = barcode.rect
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
            
            barcodeData = barcode.data.decode("utf-8")
            
            print("barcodes: ", barcodeData)
            
#            for i in range(1):
#                Arduinouno_Serial.write('0'.encode())
#                time.sleep(4.0)
                
#            if barcodeData not in found:
#                csv.write("{},{}\n".format(datetime.datetime.now(), barcodeData))
#                csv.flush()
#                found.add(barcodeData)
                
        #Arduinouno_Serial.write('1'.encode())
        
        
        frame = frame[y1:y2,x1:x2]#ignore
        cv2.rectangle(frame_org, (x1, y1), (x2, y2), (0,125,0), 2)
        hsv  = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        
        #Blue Color
        #low_blue = np.array([101, 50, 38])
        #high_blue = np.array([110, 255, 255])
        
        #white
        low_white = np.array([0,0,0])
        high_white = np.array([0,10,225])
        
        low_ = np.array([0,0,0])
        high_ = np.array([180,255,255])
        
        low = np.array([0,10,10])
        high = np.array([180,255,255])
        
        #black
        #low_black = np.array([0,0,0])
        #high_black = np.array([225,225,0])
        
        #Green color
        #low_green = np.array([40,50,50])
        #high_green = np.array([80,255,255])
        
        #red color
        #low_red1 = np.array([0,100,100])
        #high_red1 = np.array([10,255,255])
        
        #low_red2 = np.array([160,100,100])
        #high_red2 = np.array([179,255,255])
        
        #image_mask_red1 = cv2.inRange(hsv, low_red1, high_red1)
        #image_mask_red2 = cv2.inRange(hsv, low_red2, high_red2)
        #image_mask_blue = cv2.inRange(hsv, low_blue, high_blue)
        image_mask_white = cv2.inRange(hsv, low_white, high_white)
        #image_mask_black = cv2.inRange(hsv, low_white, high_black)
        #image_mask_green = cv2.inRange(hsv, low_green, high_green )
        image_mask_ = cv2.inRange(hsv, low_, high_)
        image_mask = cv2.inRange(hsv, low, high)
        
        image_mask_black = image_mask_ - image_mask
#try to make more precise
        #output_red1 = cv2.bitwise_and(frame, frame, mask = image_mask_red1)
        #output_red2 = cv2.bitwise_and(frame, frame, mask = image_mask_red2)
        #output_blue = cv2.bitwise_and(frame, frame, mask = image_mask_blue)
        output_black = cv2.bitwise_and(frame, frame, mask = image_mask_black)
        output_white = cv2.bitwise_and(frame, frame, mask = image_mask_white)
        #output_black = cv2.bitwise_and(frame, frame, mask = image_mask_black)
        #output_green = cv2.bitwise_and(frame, frame, mask = image_mask_green)

        #if output_red1.any() == True:
        #    print("Red_light_range")
        #elif output_red2.any() == True:
        #    print("Red_dark_range")
# a little confusinon b/w running &, or in the code
        
        #barcode()
        
        if image_mask_black.any() == True & image_mask_white.any() == True:
#            Arduinouno_Serial.write('1'.encode())
            print("Run")
        #elif output_black.any() == True:
        #    print("black_color")
        #elif output_green.any() == True:
        #    print("green_color")
        else:
#            Arduinouno_Serial.write('0'.encode())
            print("Stop")

        cv2.imshow("original Webcam Feed", frame_org)
        cv2.imshow("cutout",frame)
        cv2.imshow("Barcode Scanner", frame)
        #cv2.imshow("Image mask", image_mask_red1)
        #cv2.imshow("Image mask", image_mask_red2)
        #cv2.imshow("Image mask", image_mask_blue)
        cv2.imshow("Image mask", image_mask_black)
        cv2.imshow("Image mask", image_mask_white)
        #cv2.imshow("Image_mask", image_mask_black)
        #cv2.imshow("Image mask", image_mask_green)
        #cv2.imshow("color Tracking",output_red1)
        #cv2.imshow("color Tracking",output_red2)
        #cv2.imshow("color Tracking",output_blue)
        cv2.imshow("color Tracking",output_black)
        cv2.imshow("color Tracking",output_white)
        #cv2.imshow("color Tracking",output_black)
        #cv2.imshow("color Tracking",output_green)
        
        
        if cv2.waitKey(1) == 27:
            break
    
    print("[INFO] cleaning up...")
    cv2.destroyAllWindows()
    #csv.close()
    vs.stop()
    #cap.release()
#    Arduinouno_Serial.write('0'.encode())

if __name__=="__main__":
    main()
