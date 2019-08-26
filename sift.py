import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

file='/media/adas/Data/dynamic_data/image_1/0.jpg'
img=cv.imread(file)
# gray=cv.cvtColor(img,cv.COLOR_BGR2GRAY)
#
# sift= cv.xfeatures2d.SIFT_create()
# kpt,des=sift.detectAndCompute(gray,None)
# img=cv.drawKeypoints(gray,kpt,img)#flags=cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
# plt.imshow(img)
# plt.show()

#参数为hessian矩阵的阈值
surf = cv.xfeatures2d.SURF_create(4000)
#找到关键点和描述符
key_query,desc_query = surf.detectAndCompute(img,None)
#把特征点标记到图片上
img=cv.drawKeypoints(img,key_query,img)

cv.imshow('sp',img)
cv.waitKey(0)