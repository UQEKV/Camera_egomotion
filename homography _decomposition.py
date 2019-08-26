import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import pandas as pd

H=np.mat([[0.003893535402747,-0.000034137362969,-1.692995600866291],
          [0.000098054080473,0.001656597132951,-0.345288710515408],
         [-0.000044016914558,-0.003524815539918,1.000000000000000]])

Homo=np.mat(np.array([[-0.000741332467697,-0.003436565571942,1.487094241414396],
            [0.002083160954695,-0.000678130397264,-0.421949850006257],
            [-0.002750655772836,0.000510304217662,1.000000000000000]]))
print('Homograpy Matrix \n',H)


U,sigma,VT=np.linalg.svd(H)
sigma=np.mat(np.diag(sigma))
print('U\n',U)
print('sigma\n',sigma)
print('VT\n',VT)

Lambda= np.diag(np.multiply(sigma,sigma)).tolist()
Lambda.sort(reverse=True)
Lambda1=Lambda[0]
Lambda2=Lambda[1]
Lambda3=Lambda[2]
print('Lambda1: ',Lambda1,'Lambda2: ',Lambda2,'Lambda3: ', Lambda3)

s=np.linalg.det(U)*np.linalg.det(VT.H)
print('s:', s)