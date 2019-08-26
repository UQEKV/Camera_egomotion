import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
from numpy import matrix as mat
from matplotlib import pyplot as plt
import random


apple=np.mat(["a",'b'],['c','d'])
print(apple)

#
# def feature_matching(i, knn_distance):  # overlap_img1_u1,overlap_img1_u2,overlap_img2_u1,overlap_img2_u2,knn_distance):
#     img1 = data_0[i][0:400, 0:650]  # ,overlap_img1_u1:overlap_img1_u2]
#     img2 = data_1[i][0:400, 730:1280]  # ,overlap_img2_u1:overlap_img2_u2]
#     # Initiate SIFT detector
#     sift = cv.xfeatures2d.SIFT_create()
#     # find the keypoints and descriptors with SIFT
#     kp1, des1 = sift.detectAndCompute(img1, None)
#     kp2, des2 = sift.detectAndCompute(img2, None)
#     # BFMatcher with default params
#     bf = cv.BFMatcher()
#     matches = bf.knnMatch(des1, des2, k=2)
#     # Apply ratio test
#     good = []
#     for m, n in matches:
#         if m.distance < knn_distance * n.distance:
#             good.append([m])
#     # cv.drawMatchesKnn expects list of lists as matches.
#     img3 = cv.drawMatchesKnn(img1, kp1, img2, kp2, good, None, flags=cv.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
#     cv.imwrite('/media/adas/Data/dynamic_data/matching/' + str(i) + '.jpg', img3)
#     # cv.namedWindow("img3", cv.WINDOW_NORMAL)
#     # cv.resizeWindow('img3', 1600, 1000)
#     # cv.imshow("img3",img3)
#     # cv.waitKey(0)& 0xFF == ord('q')
#     # cv.destroyAllWindows()
#
#     return img3, good, kp1, kp2
