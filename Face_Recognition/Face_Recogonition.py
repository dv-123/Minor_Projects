# -*- coding: utf-8 -*-
"""
Created on Thu Aug 22 20:33:25 2019

@author: bhaik
"""

from keras.models import Sequential
from keras.layers import Conv2D, ZeroPadding2D, Activation, Input, concatenate
from keras.models import Model
from keras.layers.normalization import BatchNormalization
from keras.layers.pooling import MaxPooling2D, AveragePooling2D
from keras.layers.merge import Concatenate
from keras.layers.core import Lambda, Flatten, Dense
from keras.initializers import glorot_uniform
from keras.engine.topology import Layer
from keras import backend as K
K.set_image_data_format('channels_first')
import cv2
import os
import numpy as np
from numpy import genfromtxt
import pandas as pd
import tensorflow as tf
from fr_utils import *
from inception_blocks_v2 import *
import pickle

FRmodel = faceRecoModel(input_shape=(3, 96, 96))
print("Total Params:", FRmodel.count_params())

def triplet_loss(y_true, y_pred, alpha = 0.2):

    anchor, positive, negative = y_pred[0], y_pred[1], y_pred[2]

    pos_dist = tf.reduce_sum(tf.square(tf.subtract(anchor,positive)),axis=-1)
    neg_dist = tf.reduce_sum(tf.square(tf.subtract(anchor,negative)),axis=-1)
    basic_loss = tf.add(tf.subtract(pos_dist,neg_dist),alpha)
    loss = tf.reduce_sum(tf.maximum(basic_loss,0))

    return loss

with tf.Session() as test:
    tf.set_random_seed(1)
    y_true = (None, None, None)
    y_pred = (tf.random_normal([3, 128], mean=6, stddev=0.1, seed = 1),
              tf.random_normal([3, 128], mean=1, stddev=1, seed = 1),
              tf.random_normal([3, 128], mean=3, stddev=4, seed = 1))
    loss = triplet_loss(y_true, y_pred)

    print("loss = " + str(loss.eval()))

FRmodel.compile(optimizer = 'adam', loss = triplet_loss, metrics = ['accuracy'])
load_weights_from_FaceNet(FRmodel)


with open('database.p','rb') as fp:
    database = pickle.load(fp)

condition = False

def verify(image_path, identity, database, model):

    img1=image_path
    img = img1[...,::-1]
    img = np.around(np.transpose(img, (2,0,1))/255.0, decimals=12)
    x_train = np.array([img])
    embedding = model.predict_on_batch(x_train)
    encoding = embedding

    dist = np.linalg.norm(encoding-database[identity])

    if dist < 0.5:
        condition = True
    else:
        condition = False

    return dist, door_open

# using video feed as infput for verify function
#cap = cv2.VideoCapture(1)

#while True:

#    ret, frame = cap.read()
#    img = cv2.resize(frame,(96,96),interpolation = cv2.INTER_CUBIC)
#    for i in range(1,16,1):
#        dist, door_open = verify(img,"DV_"+str(i),database, FRmodel)
#        if condition == True:
#            print("DV!")
        #else:
        #    print("not DV!")
#    image = cv2.resize(img,(1280,720),interpolation = cv2.INTER_CUBIC)

    #draw_boxes(image, out_scores, out_boxes, out_classes, class_names, colors)


#    cv2.imshow("output",frame)


#    if cv2.waitKey(1) & 0xFF == ord('q'):
#        break


#cap.release()
#cv2.destroyAllWindows()


def who_is_it(image_path, database, model):

    img1=image_path
    img = img1[...,::-1]
    img = np.around(np.transpose(img, (2,0,1))/255.0, decimals=12)
    x_train = np.array([img])
    embedding = model.predict_on_batch(x_train)
    encoding = embedding
    #encoding = img_to_encoding(image_path, model)

    min_dist = 100

    for (name, db_enc) in database.items():

        dist = np.linalg.norm(encoding - db_enc)

        if dist < min_dist:
            min_dist = dist
            identity = name

    #if min_dist > 0.5:
    #    print("Not in the database.")
    #else:
    #    print ("it's " + str(identity) + ", the distance is " + str(min_dist))

    return min_dist, identity

a = 0
face_cascade = cv2.CascadeClassifier("haarcascade-frontalface-alt.xml")
out_path = "Saved_image.jpg"
cap = cv2.VideoCapture(0)
scaling_factor = 0.5
while True:
    ret,frame = cap.read()
    img = frame
    frame = cv2.resize(frame, None, fx=scaling_factor,fy=scaling_factor, interpolation=cv2.INTER_AREA)
    face_rects = face_cascade.detectMultiScale(frame, scaleFactor=1.3, minNeighbors=3)

    cv2.imshow("Face Detection", img)

    for(x,y,w,h) in face_rects:
        cv2.rectangle(frame, (x,y), (x+w,y+h), (0,0,255), 3)
        cv2.imwrite(out_path,img)
        image = cv2.imread(out_path)
        image = cv2.resize(image,(96,96),interpolation = cv2.INTER_CUBIC)
        min_dist, identity = who_is_it(image, database, FRmodel)
        if min_dist > 0.4:
            a = 1
            print("it's"+str(identity)+"! welcome to program")
            break

    #if a == 1:
    #    break
    c = cv2.waitKey(1)
    if c == 27:
        break

cap.release()
cv2.destroyAllWindows()
