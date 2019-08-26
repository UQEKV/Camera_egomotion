from scipy.ndimage import filters
import cv2
from matplotlib.pylab import *

filename = '/home/adas/Documents/images/right/0000.png'
file1='/media/adas/Data/dynamic_data/roi/image_roi_1.png'
file='/media/adas/Data/dynamic_data/image_1/0.jpg'
file_lap='/media/adas/Data/dynamic_data/roi/lap.jpg'

img = cv2.imread(file,0)
# 创建一个窗口
cv2.namedWindow("image", flags= cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)
cv2.namedWindow("image_roi", flags= cv2.WINDOW_NORMAL | cv2.WINDOW_FREERATIO)

cv2.imshow("image", img)
# 是否显示网格
showCrosshair = True
# 如果为Ture的话 , 则鼠标的其实位置就作为了roi的中心
# False: 从左上角到右下角选中区域
fromCenter = False
# Select ROI
rect = cv2.selectROI("image", img, showCrosshair, fromCenter)

print("选中矩形区域")
(x, y, w, h) = rect

# Crop image
imCrop = img[y : y+h, x:x+w]

# Display cropped image
cv2.imshow("image_roi", imCrop)
cv2.imwrite(file1, imCrop)
cv2.waitKey(0)