from cv2  import cv2
import os
from os.path import realpath, dirname

# 获取当前文件的全路径名
file_path = os.path.realpath(__file__)

# 上上级目录
parent_dir = os.path.dirname(os.path.dirname(file_path))

image_path = parent_dir+"/Resources/cathy.png"

print(image_path)
img = cv2.imread(image_path)

imgGray = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)

cv2.imshow("origin image",img)
cv2.imshow("gray image",img)


cv2.waitKey(0) 