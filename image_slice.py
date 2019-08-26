from __future__ import print_function
import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os
import  shutil

path='/media/adas/Data/dynamic_data/newdata'
filelist=os.listdir(path)
filelist.sort()
print(filelist)
def img_slice(i,row1,row2,camera_number):
    img=cv.imread('/media/adas/Data/dynamic_data/newdata/'+filelist[i])
    img=cv.cvtColor(img,cv.COLOR_BGR2GRAY)
    img_new=img[row1:row2,:]
    cv.imwrite('/media/adas/Data/dynamic_data/img%d/'%(camera_number) + str(i) + ".jpg", img_new)
    return img_new

img0=[img_slice(i,0,720,0) for i in range(len(filelist))]
img1=[img_slice(i,720,720*2,1) for i in range(len(filelist))]
img2=[img_slice(i,720*2,720*3,2) for i in range(len(filelist))]
img3=[img_slice(i,720*3,720*4,3) for i in range(len(filelist))]



