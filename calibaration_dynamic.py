import cv2 as cv
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import re
matching00=pd.read_csv('/media/adas/Data/dynamic_data/data/k00.csv')
matching01=pd.read_csv('/media/adas/Data/dynamic_data/data/k01.csv')
matching11=pd.read_csv('/media/adas/Data/dynamic_data/data/k11.csv')
matching12=pd.read_csv('/media/adas/Data/dynamic_data/data/k12.csv')
matching22=pd.read_csv('/media/adas/Data/dynamic_data/data/k22.csv')
matching23=pd.read_csv('/media/adas/Data/dynamic_data/data/k23.csv')
matching33=pd.read_csv('/media/adas/Data/dynamic_data/data/k33.csv')
matching30=pd.read_csv('/media/adas/Data/dynamic_data/data/k30.csv')

def extract_row (i,data_camera):    #for every frame
    row=[]
    a=data_camera.values.tolist()[i]
    c=[i for i in a  if str(i) != "nan"]
    for j in range(len(c)):
        d=re.findall(r'[(](.*?)[)]', c[j])
        x=float(d[0].split(',')[0])
        y=float(d[0].split(',')[1])
        point=[x,y]
        row.append(point)

    return row

cam00_data=[extract_row(i,matching00) for i in range(len(matching00))]
cam01_data=[extract_row(i,matching01) for i in range(len(matching01))]
cam11_data=[extract_row(i,matching11) for i in range(len(matching11))]
cam12_data=[extract_row(i,matching12) for i in range(len(matching12))]
cam22_data=[extract_row(i,matching22) for i in range(len(matching22))]
cam23_data=[extract_row(i,matching23) for i in range(len(matching23))]
cam33_data=[extract_row(i,matching33) for i in range(len(matching33))]
cam30_data=[extract_row(i,matching30) for i in range(len(matching30))]


# we define methods for every picture

def roi_renew_data1 (cam_data1,j):      #selecting the feature in region of interest
    k1=[]
    for i in cam_data1[j]:
        if 20<=i[0]<=650 and 0<=i[1]<=400:
            k1.append(i)
        else:
            k1.append([])
    return k1

def roi_renew_data2 (cam_data2,j):
    k2=[]
    for i in cam_data2[j]:
        if 730 <= i[0] < 1280 and 0 <= i[1] <= 400:
            k2.append(i)
        else:
            k2.append([])
    return k2

test00=[roi_renew_data1(cam00_data,i)  for i in range(len(cam00_data))]
test01=[roi_renew_data2(cam01_data,i)  for i in range(len(cam01_data))]
test11=[roi_renew_data1(cam11_data,i)  for i in range(len(cam11_data))]
test12=[roi_renew_data2(cam12_data,i)  for i in range(len(cam12_data))]
test22=[roi_renew_data1(cam22_data,i)  for i in range(len(cam22_data))]
test23=[roi_renew_data2(cam23_data,i)  for i in range(len(cam23_data))]
test33=[roi_renew_data1(cam33_data,i)  for i in range(len(cam33_data))]
test30=[roi_renew_data2(cam30_data,i)  for i in range(len(cam30_data))]
print(len(test00))
print(len(test01))
print(len(test11))
print(len(test12))
print(len(test22))
print(len(test23))# in the end of the list may not have some features, so the additional list of the keypoints will be lost in the loop
print(len(test33))
print(len(test30))



def data_end1 (j,data1,data2):     # some matchings may not be best and some errors will appear
    in_list1 = []  # some feature points may be selected in roi and the another
    if len(data1[j]) != len(data2[j]):
        in_list1=[]
    else:
        for i in range(len(data1[j])):  #will be removed, so we must define a method to removed the error
            if len(data1[i])==0 or len(data2[i])==0 :
                in_list1.append([])
            else:
                if len(data1[j][i]) == len(data2[j][i]):
                    in_list1.append(data1[j][i])
                else:
                    in_list1.append([])
    return in_list1

def data_end2 (j,data1,data2):
    in_list2 = []
    if len(data1[j]) != len(data2[j]):    # some matchings can come to error(the number of matching points is not the same so removing all the points and note it as []
        in_list2=[]
    else:
        for i in range(len(data2[j])):
            if len(data2[i])==0 or len(data1[i])==0 :
                in_list2.append([])
            else:
                if len(data1[j][i]) == len(data2[j][i]):
                    in_list2.append(data2[j][i])
                else:
                    in_list2.append([])
    return in_list2


data00=[data_end1(i,test00,test01) for i in range(588)]
data01=[data_end2(i,test00,test01) for i in range(588)]
data11=[data_end1(i,test11,test12) for i in range(588)]
data12=[data_end2(i,test11,test12) for i in range(588)]
data22=[data_end1(i,test22,test23) for i in range(588)]
data23=[data_end2(i,test22,test23) for i in range(588)]
data33=[data_end1(i,test33,test30) for i in range(588)]
data30=[data_end2(i,test33,test30) for i in range(588)]
# print(data00)
# print(data01)
# print(data11)
# print(data12)
# print(data22)
# print(data23)
# print(data33)
# print(data30)

feature_points=[]
for i in range(588):
    feature_points.append(data00[i]+data01[i]+data11[i]+data12[i]+data22[i]+data23[i]+data33[i]+data30[i])

print(len(feature_points))


def remove_empty (number_image):
    feature_point=[]
    for i in feature_points[number_image]:
        if i!= []:
           feature_point.append(i)
    return feature_point

feature_data=[remove_empty(i) for i in range(588)]


print(feature_data)
print(len(feature_data))
