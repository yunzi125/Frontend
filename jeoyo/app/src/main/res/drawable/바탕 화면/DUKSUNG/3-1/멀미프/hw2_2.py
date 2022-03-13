import numpy as np
import cv2, pafy
# 동영상 열기
url = 'https://youtu.be/DXsxkEn59m0'
video = pafy.new(url)
best = video.getbest(preftype='mp4')
cap = cv2.VideoCapture(best.url)
if not cap.isOpened(): raise Exception("동영상파일 개방 안됨")
ret1, frame1 = cap.read()
#첫 프레임 읽어오기
#bgr을hsv로 변환 후 hsv를 분리
hsv = cv2.cvtColor(frame1, cv2.COLOR_BGR2HSV)
h, s, v = cv2.split(hsv)
# 첫 프레임에서 색상을 선택하여 채도값을 얻는다.
roi = cv2.selectROI('img', frame1)
roi_h = h[roi[1]:roi[1]+roi[3], roi[0]+roi[2]]
while True:
    ret, frame = cap.read()
    if not ret:
        break
    cv2.imshow('frame', frame)
    # bgr을hsv로 변환 후hsv를 분리
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    h, s, v = cv2.split(hsv)
    # 선택 영역의h를 히스토그램으로 만들고 역투영하기
    hist = cv2.calcHist([roi_h], [0], None, [64], [0, 256])
    backP = cv2.calcBackProject([h.astype(np.float32)], [0], hist, [0, 256], scale=1.0)
    hist = cv2.sort(hist, cv2.SORT_EVERY_COLUMN + cv2.SORT_DESCENDING)
    k = 1
    T = hist[k][0] -1
    ret, dst = cv2.threshold(backP, T, 255, cv2.THRESH_BINARY)
    # 이미지에 마스크를 적용하여and연산을 시킴
    color_img = cv2.bitwise_and(frame, frame, mask=dst.astype(np.uint8))
    cv2.imshow('frame_after', color_img)
    key = cv2.waitKey(25)
    if key == 27:
        break


if cap.isOpened():
    cap.release()
    cv2.destroyAllWindows()