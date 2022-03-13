import numpy as np
import cv2

image = cv2.imread("image/2.jpeg", cv2.IMREAD_COLOR)
if image is None: raise Exception("영상파일 읽기 오류")
global minV, maxV

def onChange(x):
    minV = cv2.getTrackbarPos('V_min', title) ##V_min 트랙바에서  값 가져오기
    maxV = cv2.getTrackbarPos('V_max', title) ##V_max 트랙바에서  값 가져오기
    hsvImg = cv2.cvtColor(image, cv2.COLOR_BGR2HSV) ##V에 대한 이진화를 수행해주어야하므로 HSV로 변경
    h, s, v = cv2.split(hsvImg) ##V를 추출

    th, minImg = cv2.threshold(v, minV, 255, cv2.THRESH_TOZERO) ##min보다 작으면 0, 크면 그대로여야하므로 cv2.THRESH_TOZERO로 설정
    th, maxImg = cv2.threshold(v, maxV, 255, cv2.THRESH_TOZERO_INV) ##max보다 크면 0, 작으면 그대로여야하므로 cv2.THRESH_TOZERO_INV로 설정
    addImg = cv2.bitwise_and(minImg, maxImg) ##두 이미지를 합쳐 min보다 크고 max보다 작은 곳에 대해 이진화를 진행한 이미지를 생성
    hsvImg2 = cv2.merge([h, s, addImg])
    last = cv2.cvtColor(hsvImg2, cv2.COLOR_HSV2BGR) ##다시 원본으로 되돌림
    cv2.imshow(title, last)

title='hw2_1'
cv2.imshow(title, image)

##트랙바 생성 및 초기값 지정
cv2.createTrackbar('V_min', title, 0, 255, onChange)
cv2.setTrackbarPos('V_min', title, 0)
cv2.createTrackbar('V_max', title, 0, 255, onChange)
cv2.setTrackbarPos('V_max', title, 255)

cv2.waitKey()
cv2.destroyAllWindows()



