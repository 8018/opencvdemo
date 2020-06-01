import numpy as np
from cv2 import cv2
from matplotlib import pyplot as plt

img = cv2.imread("../Resources/cathy.png")
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

 # 生成 5 X 5的平均滤波器核
kernel = np.ones((5, 5), np.float32) / 25

average = cv2.filter2D(img, -1, kernel)

blur = cv2.blur(img, (50, 50))

plt.subplot(121), plt.imshow(img), plt.title("Original")
plt.subplot(122), plt.imshow(average), plt.title("Average")
plt.subplot(123), plt.imshow(blur), plt.title("Blur")

plt.show()