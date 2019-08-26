from __future__ import print_function
import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os

path='/media/adas/Data/dynamic_data/newdata'
filelist=os.listdir(path)
print(len(filelist))
def read_image(i,camera_number):
    img=cv.imread('/media/adas/Data/dynamic_data/img%d/'%(camera_number) + str(i) + ".jpg")
    return img

data_0=[read_image(i,0) for i in range(100)]
data_1=[read_image(i,1) for i in range(100)]
data_2=[read_image(i,2) for i in range(100)]
data_3=[read_image(i,3) for i in range(100)]

def feature_matching (i,data_cameraNum1,data_cameraNum2,matching_number,knn_distance):
      img1=data_cameraNum1[i]
      img2=data_cameraNum2[i]
      # Initiate SIFT detector
      sift = cv.xfeatures2d.SIFT_create()
      # find the keypoints and descriptors with SIFT
      kp1, des1 = sift.detectAndCompute(img1, None)
      kp2, des2 = sift.detectAndCompute(img2, None)
      # BFMatcher with default params
      bf = cv.BFMatcher()
      matches = bf.knnMatch(des1, des2, k=2)
      # Apply ratio test
      good = []
      for m, n in matches:
            if m.distance < knn_distance * n.distance:
                  good.append([m])
      # cv.drawMatchesKnn expects list of lists as matches.
      img3 = cv.drawMatchesKnn(img1, kp1, img2, kp2, good, None, flags=cv.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
      cv.imwrite('/media/adas/Data/dynamic_data/m%d/'%matching_number+str(i)+'.jpg',img3)
      # cv.namedWindow("img3", cv.WINDOW_NORMAL)
      # cv.resizeWindow('img3', 1600, 1000)
      # cv.imshow("img3",img3)
      # cv.waitKey(0)& 0xFF == ord('q')
      # cv.destroyAllWindows()

      return img3,good,kp1,kp2



def keyPoints (pictureNum,data_cameraNum1,data_cameraNum2,matching_number,knn_distance):  #find the keypoints and put it in a list and eliminate the same points
      kp1_list = []
      kp2_list = []
      for i in range(pictureNum):
            a, b, c, d = feature_matching(i,data_cameraNum1,data_cameraNum2,matching_number, knn_distance)
            if len(b)==0:
                  kp1_img=[]
                  kp1_list.append(kp1_img)
                  kp2_img=[]
                  kp2_list.append(kp2_img)
            else :
                kp1_in_list = []
                for j in range(len(b)):
                    kp1_img=c[b[j][0].queryIdx].pt
                    #if 20<=kp1_img[0]<=650 and 0<=kp1_img[1]<=400:
                    kp1_in_list.append(kp1_img)
                new_list1=[]
                for point in kp1_in_list:
                    if point not in new_list1:
                        new_list1.append(point)
                kp1_in_list=new_list1
                kp1_list.append(kp1_in_list)

                kp2_in_list = []
                for k in range(len(b)):
                    kp2_img=d[b[k][0].trainIdx].pt
                    #if 730 <= kp2_img[0] < 1280 and 0 <= kp2_img[1] <= 400:
                    kp2_in_list.append(kp2_img)
                new_list2=[]
                for point in kp2_in_list:
                    if point not in new_list2:
                        new_list2.append(point)
                kp2_in_list=new_list2
                kp2_list.append(kp2_in_list)
      return kp1_list, kp2_list


k00,k01=keyPoints(100,data_0,data_1,0,0.7)
k11,k12=keyPoints(100,data_1,data_2,1,0.7)
k22,k23=keyPoints(10,data_2,data_3,2,0.7)
k33,k30=keyPoints(10,data_3,data_0,3,0.7)

k00=pd.DataFrame(k00)
k01=pd.DataFrame(k01)
k11=pd.DataFrame(k11)
k12=pd.DataFrame(k12)
k22=pd.DataFrame(k22)
k23=pd.DataFrame(k23)
k33=pd.DataFrame(k33)
k30=pd.DataFrame(k30)

# k00.to_csv('/media/adas/Data/dynamic_data/data/k00.csv',encoding='utf-8')
# k01.to_csv('/media/adas/Data/dynamic_data/data/k01.csv',encoding='utf-8')
# k11.to_csv('/media/adas/Data/dynamic_data/data/k11.csv',encoding='utf-8')
# k12.to_csv('/media/adas/Data/dynamic_data/data/k12.csv',encoding='utf-8')
# k22.to_csv('/media/adas/Data/dynamic_data/data/k22.csv',encoding='utf-8')
# k23.to_csv('/media/adas/Data/dynamic_data/data/k23.csv',encoding='utf-8')
# k33.to_csv('/media/adas/Data/dynamic_data/data/k33.csv',encoding='utf-8')
# k30.to_csv('/media/adas/Data/dynamic_data/data/k30.csv',encoding='utf-8')




