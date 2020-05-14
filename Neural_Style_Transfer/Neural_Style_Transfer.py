import os
import sys
import scipy.io
from skimage.io import imread, imshow
import matplotlib.pyplot as plt
from PIL import Image
from utils import *
import numpy as np
import tensorflow as tf
from tqdm import tqdm


def compute_content_cost(a_C, a_G):


    m, n_H, n_W, n_C = a_G.get_shape().as_list()
    # a_C is a tensor of dimension (1, n_H, n_W, n_C),
    # hidden layer activations representing content of the image C
    a_C_unrolled = tf.transpose(tf.reshape(a_C, [-1]))
    # a_G is a tensor of dimension (1, n_H, n_W, n_C),
    # hidden layer activations representing content of the image G
    a_G_unrolled = tf.transpose(tf.reshape(a_G, [-1]))

    J_content = tf.reduce_sum(tf.square(tf.subtract(a_C_unrolled,a_G_unrolled))) / (4 * n_H * n_W * n_C)

    return J_content


def gram_matrix(A):

    # A is a matrix of shape (n_C, n_H*n_W)
    # GA is a Gram matrix of A, of shape (n_C, n_C)
    GA = tf.matmul(A, tf.transpose(A))

    return A


def compute_layer_style_cost(a_S, a_G):

    m, n_H, n_W, n_C = a_G.get_shape().as_list()

    a_S = tf.reshape(a_S, [n_H*n_W, n_C])
    a_G = tf.reshape(a_G, [n_H*n_W, n_C])

    GS = gram_matrix(tf.transpose(a_S))
    GG = gram_matrix(tf.transpose(a_G))

    J_style_layer = tf.reduce_sum((GS - GG)**2) / (4 * n_C**2 * (n_W * n_H)**2)

    return J_style_layer


def compute_style_cost(model, STYLE_LAYERS):

    J_style = 0

    for layer_name, coeff in STYLE_LAYERS:
        out = model[layer_name]

        a_S = sess.run(out)

        a_G = out

        J_style_layer = compute_layer_style_cost(a_S, a_G)
        J_style =+ coeff*J_style_layer

    return J_style


# important in changing the aperances
def total_cost(J_content, J_style, alpha = 60, beta = 6000000):
    # the effect of style loss must be much grater than the content loss.
    J = (alpha*J_content) + (beta*J_style)

    return J

def model_nn(sess, input_image, num_iterations = 1000):

    sess.run(tf.global_variables_initializer())

    sess.run(model['input'].assign(input_image))

    for i in tqdm(range(num_iterations)):
        sess.run(train_step)

        generate_image = sess.run(model['input'])

        if i%50 == 0:
            Jt, Jc, Js = sess.run([J, J_content, J_style])
            print("Iteration " + str(i) + " :")
            print("total cost = " + str(Jt))
            print("content cost = " + str(Jc))
            print("style cost = " + str(Js))

            save_image("output/" + str(i) + ".png", generate_image)

    save_image('output/generated_image.jpg', generate_image)

    return generate_image


# defining the style layers
STYLE_LAYERS = [
    ('conv1_1', 0.2),
    ('conv2_1', 0.2),
    ('conv3_1', 0.2),
    ('conv4_1', 0.2),
    ('conv5_1', 0.2)]


tf.reset_default_graph()

sess = tf.InteractiveSession()


# loading the content_image
print("Loading and showing content image !")
content_image = imread(CONFIG.CONTENT_IMAGE)
content_image = resize_reshape_and_normalize_image(content_image)
imshow(content_image[0])
plt.show()


# Loading Style image
print("Loading and showing Style image !")
style_image = imread(CONFIG.STYLE_IMAGE)
style_image = resize_reshape_and_normalize_image(style_image)
imshow(style_image[0])
plt.show()

# making the noisy image
print("Generating and showing noisy image !")
generate_image = generate_noise_image(content_image)
imshow(generate_image[0])
plt.show()


# loading VGG-19 model
print("Loading VGG-19 model !")
model = load_vgg_model(CONFIG.VGG_MODEL)
print(model)


sess.run(model['input'].assign(content_image))
out = model['conv5_2']
a_C = sess.run(out)
a_G = out
J_content = compute_content_cost(a_C, a_G)

sess.run(model['input'].assign(style_image))
J_style = compute_style_cost(model, STYLE_LAYERS)

J = total_cost(J_content=J_content,J_style=J_style)


optimizer = tf.train.AdamOptimizer(2.0)
train_step = optimizer.minimize(J)

model_nn(sess, generate_image)
