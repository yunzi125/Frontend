import cv2

def onTrackbar(th):																	# 트랙바 콜백 함수
	rep_edge = cv2.GaussianBlur(rep_gray, (5, 5), 0)         	# 가우시안 블러링
	rep_edge = cv2.Canny(rep_edge, th, th*2, 5)						# 캐니 에지 검출
	h, w = image.shape[:2]
	cv2.rectangle(rep_edge, (0, 0, w, h), 255, -1)    						# 흰색 사각형 그리기
	color_edge = cv2.bitwise_and(rep_image, rep_image, mask=rep_edge)
	cv2.imshow("color edge", color_edge)

image = cv2.imread("images/color_edge.jpg", cv2.IMREAD_COLOR)
if image is None: raise Exception("영상파일 읽기 오류")

th = 50
rep_image = cv2.repeat(image, 1, 2)                      	# 가로 반복 복사
rep_gray = cv2.cvtColor(rep_image, cv2.COLOR_BGR2GRAY)    	# 명암도 영상 변환

cv2.namedWindow("color edge", cv2.WINDOW_AUTOSIZE)    		# 윈도우 생성
cv2.createTrackbar("Canny th", "color edge", th, 100, onTrackbar)	# 콜백 함수 등록
onTrackbar(th)																					# 콜백 함수 첫 실행
cv2.waitKey(0)