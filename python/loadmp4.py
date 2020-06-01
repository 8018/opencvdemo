from cv2 import cv2 as cv
import os
from os.path import realpath, dirname

# 获取当前文件的全路径名
file_path = os.path.realpath(__file__)

# 上上级目录
parent_dir = os.path.dirname(os.path.dirname(file_path))

video_path = parent_dir+"/Resources/test.mp4"

cap = cv.VideoCapture(video_path)

while True:
    success,img = cap.read()
    cv.imshow("capture",img)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

