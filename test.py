import libdlib_ext
import ctypes
dlib_ext = ctypes.cdll.LoadLibrary("libdlib_ext.dylib")
dlib_ext.TestFunc()
dlib_ext.TestFunc.restype = ctypes.c_char_p
dlib_ext.TestFunc()
ls
import PIL.Image
img = PIL.Image.open("/Users/lando/Desktop/laoshi.jpg")
img.shape
img.size
import numpy as np
imgdata = np.asarray(img)
imgdata
dlib.TestFunc(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
dlib_ext.TestFunc(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
dlib_ext.LoadLandmarkPredictor(b"/Users/lando/Desktop/alphaface2.0/server/bins/models/shape_predictor_68_face_landmarks.dat")
dlib_ext.LoadFaceEncoder(b"/Users/lando/Desktop/alphaface2.0/server/bins/models/dlib_face_recognition_resnet_model_v1.dat")
dlib_ext.LandmarkAndEncode(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
dlib_ext.LandmarkAndEncode.restype = ctypes.c_char_p
dlib_ext.LandmarkAndEncode(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
dlib_ext.LandmarkAndEncode(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
l = dlib_ext.LandmarkAndEncode(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
l
import json
landmarks = json.loads(l)["landmarks"]
landmarks
img
img.show()
l2 = dlib_ext.LandmarkAndEncode(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
v1 = json.loads(l)["facevector"]
v1
v2 = json.loads(l2)["facevector"]
v2
v2 - v1
d = np.array(v1)-np.array(v2)
d
gimg[1][1]
img[1][1]
help(img.point)
img.seek
help(img.seek)
help(img)
for x,y in landmarks:
    img.putpixel(x,y, [0,0,255])]
for x,y in landmarks:
    img.putpixel(x,y, [0,0,255])
help(img.putpixel)
for x,y in landmarks:
    img.putpixel((x,y), [0,0,255])
for x,y in landmarks:
    img.putpixel((x,y), (0,0,255))
img.show()
for x,y in landmarks:
    if x > 0 and y > 0:
        img.putpixel((x,y), (0,0,255))
help(img.putpixel)
from PIL import ImageDraw
draw = ImageDraw.Draw(img)
draw.ellipse
help(draw.ellipse)
for x,y in landmarks:
    if x > 2 and y > 2:
        draw.ellipse((x-2,y-2,x+2.y+2), fill=(255,0,0))
for x,y in landmarks:
    if x > 2 and y > 2:
        draw.ellipse((x-2,y-2,x+2,y+2), fill=(255,0,0))
img.show()
seeta = ctypes.cdll.LoadLibrary("seeta_ext.so")
seeta.LoadModel(b"/Users/lando/Desktop/alphaface2.0/server/bins/face_det_model.bin")
seeta.SetMinFaceSize(40)
seeta.SetScoreThresh(ctypes.c_double(2.0))
seeta.SetImagePyramidScaleFactor(ctypes.c_double(0.8))
seeta.SetWindowStep(4,4)
img.size
 r = seeta.Detect(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
seeta.Detect.restype = ctypes.c_char_p
 r = seeta.Detect(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
 r = seeta.Detect(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
seeta.Detect(imgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
grayimg = img.convert("L")
grayimgdata = np.asarray(grayimg)
seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r = seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
r = seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r = seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
r = seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
r = seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
r = seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r = seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r
r
seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
seeta.Detect(grayimgdata.ctypes.data_as(ctypes.c_char_p), 575, 548)
r = '{\n   "faces" : [\n      {\n         "h" : 158,\n         "w" : 158,\n         "x" : 223,\n         "y" : 116\n      }\n   ],\n   "msecs" : 75\n}\n'
r = json.loads(r)
r
grayimg.show()
draw.line
help(draw.line)
draw.line((223, 116, 223+158, 116+158], [255,0,0], 2)
draw.line((223, 116, 223+158, 116+158), [255,0,0], 2)
draw.line((223, 116, 223+158, 116+158), (255,0,0), 2)
img.show()
hist
img = PIL.Image.open("/Users/lando/Desktop/laoshi.jpg")
img.show()
face_region = img.crop((223, 116, 223+158, 116+158))
face_region.show()
l = dlib_ext.LandmarkAndEncode(np.asarray(face_region).ctypes.data_as(ctypes.c_char_p), 158, 158)
l
landmarks = json.loads(l)["landmarks"]
for x,y in landmarks:
    bx = x + 223
    by = y + 116
    draw.ellipse((bx-2,by-2,bx+2,by+2), fill=(0,255,0))
img.show()
draw.show()
draw = ImageDraw.Draw(img)
for x,y in landmarks:
    bx = x + 223
    by = y + 116
    draw.ellipse((bx-2,by-2,bx+2,by+2), fill=(0,255,0))
img.show()
l = dlib_ext.LandmarkAndEncode(np.asarray(face_region).ctypes.data_as(ctypes.c_char_p), 158, 158)
l
l