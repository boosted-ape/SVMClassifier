import numpy
import caffe
import sys

import os

root = "./"

if os.path.isfile(root + "models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel"):
    print ("caffe found")
else:
    print("error")
    exit

caffe.set_mode_cpu()

model_def = root + "models/bvlc_reference_caffenet/deploy.prototxt"
model_weights = root + "models/bvlc_reference_caffenet/bvlc_reference_caffenet.caffemodel"

def deprocess_image():
    image = image.copy()
    image = image[::-1]
    image = image.tranpose(1,2,0)
    image += [123, 117, 104]

    image[image<0], image[image>255] = 0, 255

    image = np.round(image)
    image = np.require(image, dtype=np.uint8)

    return image
