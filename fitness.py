import tensorflow as tf
import os
import argparse
import sys
import numpy as np

parser = argparse.ArgumentParser()
parser.add_argument(
        '--solution',
        type=str
)
parser.add_argument(
        '--type',
        type=str
)
parser.add_argument(
        '--genes',
        type=int
)

FLAGS, unparsed = parser.parse_known_args()

print(FLAGS.solution)
print(FLAGS.type)
print(FLAGS.genes)

model_path = "./TensorFlow/DNN_Models-" + str(FLAGS.genes) + "-noisy/" + FLAGS.type + str(FLAGS.genes) + ".csv/"
meta_file = '{}/model.meta'.format(model_path)
ckpt_file = '{}/checkpoint'.format(model_path)

x_ = FLAGS.solution
input_xx = x_.split('/')
input_x = list()
for i in range(0, len(input_xx)):
    if i == 0:
        input_x = input_xx[i].split(',')
    else:
        input_x = np.vstack([input_x, input_xx[i].split(',')])

input_x = np.array(input_x).reshape((len(input_xx),FLAGS.genes))
input_y = np.zeros((len(input_xx), 1))

with tf.device('/device:{}:1'.format('CPU')):
    config = tf.ConfigProto(allow_soft_placement=True)
    sess = tf.Session(config=config)
    sess.run(tf.global_variables_initializer())
    sess.run(tf.local_variables_initializer())

    model = tf.train.import_meta_graph(meta_file, clear_devices=True)
    model.restore(sess, tf.train.latest_checkpoint(model_path))

    graph = tf.get_default_graph()

    x = graph.get_tensor_by_name('input_x:0')
    y = graph.get_tensor_by_name('input_y:0')

    keep_prob = graph.get_tensor_by_name('keep_prob:0')
    y_predict = graph.get_tensor_by_name('y_predict/BiasAdd:0')

    prediction = sess.run(
            y_predict,
            feed_dict={x: input_x, y: input_y, keep_prob: 1.0}
    )

tf.reset_default_graph()
sess.close()

with open('result','w') as f:
    for i in range(0, len(input_xx)):
        f.write(str(prediction[i][0]))
        f.write(' ')
