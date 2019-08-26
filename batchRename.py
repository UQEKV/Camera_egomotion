from __future__ import print_function
import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os
import  shutil

class BatchRename():

    #rename the imge batch

    def __init__(self):
        self.path='/home/adas/Documents/left'
        self.path1 = '/home/adas/Documents/left1'

    def rename(self):
        filelist=os.listdir(self.path)
        total_num=len(filelist)
        i=0
        for item in filelist:
            if item.endswith('.png'):
                scr=os.path.join(os.path.abspath(self.path),item)
                dst = os.path.join(os.path.abspath(self.path1), ''+str(i) + '.png')#dst=os.path.join(os.path.abspath(self.path),+str(i)+'.png')

                try:
                    shutil.copy(scr,dst)
                    print('converting%s to %s...'%(scr,dst))
                    i=i+1
                except:
                    coninue
        print('total %d to rename & convert %d jpgs'%(total_num,i))

if __name__ == '__main__':
     demo=BatchRename()
     demo.rename()



