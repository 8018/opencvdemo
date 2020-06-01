from cv2 import cv2 as cv
import numpy as np


capture = cv.VideoCapture(0)                        # 创建一个VideoCapture对象

capture.set(3,640)
capture.set(4,480)

print("Hello World")
while(True):
    ret, frame = capture.read()                     # 一帧一帧读取视频

    cv.imshow('frame', frame)  # 显示结果
    if cv.waitKey(1) &0xFF == ord('q'):             # 按q停止
        break

capture.release()                                   # 释放cap,销毁窗口
cv.destroyAllWindows()