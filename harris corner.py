import cv2
import numpy as np
from matplotlib import pyplot as plt

# 读入图像并转化为float类型，用于传递给harris函数
filename = '/home/adas/Documents/images/a1.jpg'
file1='/media/adas/Data/dynamic_data/roi/image_roi.png'
file='/media/adas/Data/dynamic_data/img0/300.jpg'
file_lap='/media/adas/Data/dynamic_data/roi/lap.jpg'



# """
# Difference between goodFeaturesToTrack and Harrisdetector:
# The main difference with the Harris algorithm is that you should
# specify the minimum distance between each point, the quality level
# and the number of corners to detect.
#
# """
# #You can use this Method to detect the Harriscorners instead of goodFeaturesToTrack :
#
# #dst1 = cv2.cornerHarris(gray1, 5, 7, 0.04)
# #ret1, dst1 = cv2.threshold(dst1, 0.1 * dst1.max(), 255, 0)
# #dst1 = np.uint8(dst1)
# #ret1, labels1, stats1, centroids1 = cv2.connectedComponentsWithStats(dst1)
# #criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.001)
# #corners1 = cv2.cornerSubPix(gray1, np.float32(centroids1), (5, 5), (-1, -1),
# #criteria)
# #corners1 = np.int0(corners1)
#
#
# def correlation_coefficient(window1, window2):
#     product = np.mean((window1 - window1.mean()) * (window2 - window2.mean()))
#     stds = window1.std() * window2.std()
#     if stds == 0:
#         return 0
#     else:
#         product /= stds
#         return product
#
#
# window_size_width = 7
# window_size_height = 7
# lineThickness = 2
#
# img1 = cv2.imread('/media/adas/Data/dynamic_data/image_0/10.jpg')
# img2 = cv2.imread('/media/adas/Data/dynamic_data/image_1/10.jpg')
# width, height, ch = img1.shape[::]
# img2_copy = img2.copy()
# gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
# gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
#
# corners1 = cv2.goodFeaturesToTrack(gray1, 30, 0.01, 5)
# corners1 = np.int0(corners1)
#
# corners2 = cv2.goodFeaturesToTrack(gray2, 30, 0.01, 5)
# corners2 = np.int0(corners2)
#
# corners_windows1 = []
#
# for i in corners1:
#     x, y = i.ravel()
#     cv2.circle(img1, (x, y), 3, 255, -1)
#
# corners_windows2 = []
# for i in corners2:
#     x, y = i.ravel()
#     cv2.circle(img2, (x, y), 3, 255, -1)
#
# plt.imshow(img1), plt.show()
#
# methods = ['SSD', 'NCC']
# for method in methods:
#     matches = []
#     for id1, i in enumerate(corners1):
#         x1, y1 = i.ravel()
#         if y1 - window_size_height < 0 or y1 + window_size_height > height or x1 - window_size_width < 0 or x1 + window_size_width > width:
#             continue
#         pt1 = (x1, y1)
#         print("pt1: ", pt1)
#         template = img1[y1 - window_size_height:y1 + window_size_height, x1 - window_size_width:x1 + window_size_width]
#         max_val = 0
#         Threshold = 1000000
#         id_max = 0
#         for id2, i in enumerate(corners2):
#             x2, y2 = i.ravel()
#
#             if y2 - window_size_height < 0 or y2 + window_size_height > height or x2 - window_size_width < 0 or x2 + window_size_width > width:
#                 continue
#             window2 = img2[y2 - window_size_height:y2 + window_size_height,
#                       x2 - window_size_width:x2 + window_size_width]
#             if method == 'SSD':
#                 temp_min_val = np.sum((template - window2) ** 2)
#             elif method == 'NCC':
#                 temp_min_val = correlation_coefficient(template, window2)
#             if temp_min_val < Threshold:
#                 Threshold = temp_min_val
#                 pt2 = (x2 + 663, y2)
#         matches.append((pt1, pt2))
#     stacked_img = np.hstack((img1, img2))
#     #show the first 15 matches
#     for match in matches[:15]:
#         cv2.line(stacked_img, match[0], match[1], (0, 255, 0), lineThickness)
#     matches = []
#     plt.imshow(stacked_img)
#     plt.show()

# imag = cv2.imread(file1,0)
# img = cv2.GaussianBlur(imag,(3,3),0)
# laplacian=cv2.Laplacian(img,cv2.CV_64F)
# sobelx=cv2.Sobel(img,cv2.CV_64F,1,0,ksize=7)
# sobely=cv2.Sobel(img,cv2.CV_64F,0,1,ksize=7)
# plt.plot(),plt.imshow(laplacian,cmap = 'gray')
# plt.title('Sobel X'), plt.xticks([]), plt.yticks([])
# plt.show()
# cv2.imwrite("/media/adas/Data/dynamic_data/roi/lap.jpg", sobelx)


# # 创建一个窗口
# cv2.namedWindow("image", flags= cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)
# cv2.namedWindow("image_roi", flags= cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)
#
# cv2.imshow("image", img)
# # 是否显示网格
# showCrosshair = True
# # 如果为Ture的话 , 则鼠标的其实位置就作为了roi的中心
# # False: 从左上角到右下角选中区域
# fromCenter = False
# # Select ROI
# rect = cv2.selectROI("image", img, showCrosshair, fromCenter)
#
# print("选中矩形区域")
# (x, y, w, h) = rect
#
# # Crop image
# imCrop = img[y : y+h, x:x+w]
#
# # Display cropped image
# cv2.imshow("image_roi", imCrop)
# cv2.imwrite("/media/adas/Data/dynamic_data/roi/image_roi.png", imCrop)
# cv2.waitKey(0)

img1=cv2.imread(file)
gray_img = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
gray_img = cv2.GaussianBlur(gray_img, (7,7), 0)

gray_img = np.float32(gray_img)


# 对图像执行harris
Harris_detector = cv2.cornerHarris(gray_img, 2, 23, 0.06)

# 腐蚀harris结果
dst = cv2.dilate(Harris_detector, None)
# 设置阈值
thres = 0.00001* dst.max()

img1[dst > thres] = [255, 0, 0]
cv2.namedWindow('show', cv2.WINDOW_NORMAL)
cv2.resizeWindow('show', 1600, 1000)
cv2.imshow('show', img1)

cv2.waitKey()
asd=dst>thres

print(np.argwhere(asd==True))

