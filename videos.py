import cv2 as cv
import numpy as np

vc = cv.VideoCapture('/media/adas/ADAS_RECORDER/Rec_2019-08-14_23-40-06_ab_1.avi')

c=1
if vc.isOpened():  # 判断是否正常打开

    rval, frame = vc.read()
else:
    rval = False

timeF = 10  # 视频帧计数间隔频率

while rval:  # 循环读取视频帧
    rval,frame = vc.read()
    if (c % timeF == 0):  # 每隔timeF帧进行存储操作
        cv.imwrite('/media/adas/ADAS_RECORDER/images/' + str(c) + ".jpg", frame)  # 存储为图像

    c = c + 1
cv.waitKey(1)
vc.release()



# def read_video(file):
#     cap = cv.VideoCapture(file)
#     fps = cap.get(cv.CAP_PROP_FPS)
#     frames = cap.get(cv.CAP_PROP_FRAME_COUNT)
#     print("fps=", fps, "frames=", frames)
#     return cap
#
#
# file0='/media/adas/Data/calib/2/dw_20181203_165515_0.000000_0.000000/video_second_back.h264'
# file1='/media/adas/Data/calib/dw_20181203_170537_0.000000_0.000000/video_first_side.h264'
# file2='/media/adas/Data/calib/dw_20181203_170656_0.000000_0.000000/video_fourth_side.h264'
# #file3='/media/adas/Data/dynamic_data/Record_3.avi'
# File=[file0,file1,file2]
#
# data=[read_video(file) for file in File]
#
#
# def cap_frame(camera_number, picture_number, wait_key_number):
#     image = []
#     for i in range(picture_number):
#         ret, frame = data[camera_number].read()
#         #frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
#         cv.imwrite('/media/adas/Data/calib/image_%d/' % (camera_number) + str(i) + ".jpg", frame)
#         # cv.imshow("capture_%d"%camera_number,frame)
#         image.append(frame)
#     return image
#
# data_0=cap_frame(0,1000,20)
# data_1=cap_frame(1,1000,20)
# data_2=cap_frame(2,1000,20)
# print (np.shape(data_1[10]))