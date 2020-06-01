from cv2  import cv2
import numpy as np
import os
from os.path import realpath, dirname

# 获取当前文件的全路径名
file_path = os.path.realpath(__file__)

# 上上级目录
parent_dir = os.path.dirname(os.path.dirname(file_path))

image_path = parent_dir+"/Resources/cathy.png"

image = cv2.imread(image_path)
cv2.imshow("origin",image)


imgInfo = image.shape
print(imgInfo)

height = imgInfo[0]
width = imgInfo[1]

# 利用缩放矩阵，与之前讲述移位矩阵时类似同样拆分成两个矩阵，原理一样；改变矩阵内参数，来实现缩放
smallMat = np.float32([[0.5,0,0],[0,0.5,0]])
small = cv2.warpAffine(image,smallMat,(int(width),int(height)))# 由于高、宽*0.5，不一定为整数，所以要进行int类型强制转换
cv2.imshow("small",small)

largeMat = np.float32([[1.5,0,0],[0,1.5,0]])
large = cv2.warpAffine(image,largeMat,(width*2,height*2))# 由于高、宽*0.5，不一定为整数，所以要进行int类型强制转换
cv2.imshow("large",large)

offsetMat = np.float32([[1,0,100],[0,1,100]])
offset = cv2.warpAffine(image,offsetMat,(int(width*1.5),int(height*1.5)))# 由于高、宽*0.5，不一定为整数，所以要进行int类型强制转换
cv2.imshow("offset",offset)

theta = np.deg2rad(30)
rotateMat = np.float32([[np.cos(theta),-np.sin(theta),0],[np.sin(theta),np.cos(theta),0]])
rotate = cv2.warpAffine(image ,np.float32([[1,0,500],[0,1,0]]),(int(width*1.5),int(height*1.5)))# 由于高、宽*0.5，不一定为整数，所以要进行int类型强制转换
rotate = cv2.warpAffine(rotate,rotateMat,(int(width*1.5),int(height*1.5)))# 由于高、宽*0.5，不一定为整数，所以要进行int类型强制转换
rotate = cv2.warpAffine(rotate ,np.float32([[1,0,0],[0,1,-200]]),(int(width*1.5),int(height*1.5)))# 由于高、宽*0.5，不一定为整数，所以要进行int类型强制转换
cv2.imshow("rotate",rotate)



cv2.waitKey(0)