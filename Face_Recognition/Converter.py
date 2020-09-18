# -*- coding: utf-8 -*-
"""
Created on Sun Sep 22 21:42:12 2019

@author: bhaik
"""

import cv2
for i in range(1,16,1):
    path = "DV/DV"+str(i)+".jpg"
    print(path)
    outpath = "DV/DV_new"+str(i)+".jpg"
    
    image = cv2.imread(path)
    
    resized_image = cv2.resize(image,(96,96),interpolation = cv2.INTER_CUBIC)
    
    cv2.imwrite(outpath, resized_image)

cv2.imshow('img', resized_image)

cv2.waitKey(0)

cv2.destroyAllWindows()