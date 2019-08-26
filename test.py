import cv2 as cv
import numpy as np

video_dir = '/home/adas/PycharmProjects/dynamic_JQ/Matching_vedio.avi'
fps = 10
img_size = (640,480)
fourcc = cv.VideoWriter_fourcc('D', 'I', 'V', 'X')  # opencv3.0
videoWriter = cv.VideoWriter(video_dir, fourcc, fps,img_size)

for i in range(1000):
    v = cv.imread('/home/adas/PycharmProjects/dynamic_JQ/matching/' + str(i) + '.jpg')

    cv.imshow('video',v)
    cv.waitKey(0) & 0xFF==ord('q')
    videoWriter.write(v)

# v = cv.imread('/home/adas/PycharmProjects/dyanamic JQ/image_0/1.jpg',0)
# frame = cv.cvtColor(v, cv.COLOR_GRAY2BGR)
# cv.imshow("a",frame)
# cv.waitKey(0)
# cv.destroyAllWindows()

videoWriter.release()
cv.destroyAllWindows()

# a,b,c,d=feature_matching(247,0.53)
# print(len(b))
# print(b[1][0].queryIdx, b[1][0].trainIdx,b[0][0].queryIdx,b[0][0].trainIdx)
#
# print(c[b[0][0].queryIdx].pt)
# print(d[b[0][0].trainIdx].pt)
# print(b[0][0].distance)
# print(c[b[1][0].queryIdx].pt)
# print(d[b[1][0].trainIdx].pt)
# print(b[1][0].distance)
# print(c[b[2][0].queryIdx].pt)
# print(d[b[2][0].trainIdx].pt)
# print(b[2][0].distance)
# print(c[b[3][0].queryIdx].pt)
# print(b[3][0].trainIdx)
# print(b[3][0].distance)