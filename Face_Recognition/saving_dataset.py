# -*- coding: utf-8 -*-
"""
Created on Mon Sep 23 01:05:34 2019

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
import pickle
from fr_utils import *
from inception_blocks_v2 import *

#%matplotlib inline
#%load_ext autoreload
#%autoreload 2

#np.set_printoptions(threshold=np.nan)
#%%
FRmodel = faceRecoModel(input_shape=(3, 96, 96))
print("Total Params:", FRmodel.count_params())
#%%
# GRADED FUNCTION: triplet_loss

def triplet_loss(y_true, y_pred, alpha = 0.2):
    """
    Implementation of the triplet loss as defined by formula (3)

    Arguments:
    y_true -- true labels, required when you define a loss in Keras, you don't need it in this function.
    y_pred -- python list containing three objects:
            anchor -- the encodings for the anchor images, of shape (None, 128)
            positive -- the encodings for the positive images, of shape (None, 128)
            negative -- the encodings for the negative images, of shape (None, 128)

    Returns:
    loss -- real number, value of the loss
    """

    anchor, positive, negative = y_pred[0], y_pred[1], y_pred[2]

    ### START CODE HERE ### (≈ 4 lines)
    # Step 1: Compute the (encoding) distance between the anchor and the positive, you will need to sum over axis=-1
    pos_dist = tf.reduce_sum(tf.square(tf.subtract(anchor,positive)),axis=-1)
    # Step 2: Compute the (encoding) distance between the anchor and the negative, you will need to sum over axis=-1
    neg_dist = tf.reduce_sum(tf.square(tf.subtract(anchor,negative)),axis=-1)
    # Step 3: subtract the two previous distances and add alpha.
    basic_loss = tf.add(tf.subtract(pos_dist,neg_dist),alpha)
    # Step 4: Take the maximum of basic_loss and 0.0. Sum over the training examples.
    loss = tf.reduce_sum(tf.maximum(basic_loss,0))
    ### END CODE HERE ###

    return loss
#%%
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

filename = 'model.sav'
pickle.dump(FRmodel, open(filename,'wb'))

database = {}
#database["DV_1"] = img_to_encoding("DV/resized/DV_new1.jpg", FRmodel)
#database["DV_2"] = img_to_encoding("DV/resized/DV_new2.jpg", FRmodel)
#database["DV_3"] = img_to_encoding("DV/resized/DV_new3.jpg", FRmodel)
#database["DV_4"] = img_to_encoding("DV/resized/DV_new4.jpg", FRmodel)
#database["DV_5"] = img_to_encoding("DV/resized/DV_new5.jpg", FRmodel)
#database["DV_6"] = img_to_encoding("DV/resized/DV_new6.jpg", FRmodel)
#database["DV_7"] = img_to_encoding("DV/resized/DV_new7.jpg", FRmodel)
#database["DV_8"] = img_to_encoding("DV/resized/DV_new8.jpg", FRmodel)
database["DV_9"] = img_to_encoding("DV/resized/DV_new9.jpg", FRmodel)
#database["DV_10"] = img_to_encoding("DV/resized/DV_new10.jpg", FRmodel)
#database["DV_11"] = img_to_encoding("DV/resized/DV_new11.jpg", FRmodel)
#database["DV_12"] = img_to_encoding("DV/resized/DV_new12.jpg", FRmodel)
#database["DV_13"] = img_to_encoding("DV/resized/DV_new13.jpg",FRmodel)
#database["DV_14"] = img_to_encoding("DV/resized/DV_new14.jpg",FRmodel)
#database["DV_15"] = img_to_encoding("DV/resized/DV_new15.jpg",FRmodel)
#%%


with open('database.p','wb') as fp:
    pickle.dump(database, fp, protocol=pickle.HIGHEST_PROTOCOL)

#%%
