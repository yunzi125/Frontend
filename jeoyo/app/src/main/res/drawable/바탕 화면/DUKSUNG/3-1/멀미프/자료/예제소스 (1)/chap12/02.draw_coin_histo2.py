from Common.histogram import draw_histo_hue
from coin_preprocess import *
from coin_utils import *                            # 기타 함수

def onMouse(event, x, y, flags, param):
    global pre_img, hist_roi
    if event == cv2.EVENT_LBUTTONDOWN:          # 왼쪽 버튼 누르기
        for i, ((cx, cy), radius) in enumerate(circles):    # 메뉴아이콘 사각형 조회
            dx, dy = (cx - x), (cy - y)
            dist = np.sqrt(dx**2 + dy**2)     # 동전 중점좌표와 클릭좌표간 거리

            if dist < radius:
                hist_img = draw_histo_hue(coin_hists[i], (80, 128, 3))
                h, w = hist_img.shape[:2]
                hist_roi = [x, y, w, h]
                pre_img =  image[y:y + h, x:x + w].copy()
                image[y:y+h, x:x+w] = hist_img
                cv2.imshow("image", image)

    if event == cv2.EVENT_LBUTTONUP:            # 왼쪽 버튼 떼기
        x, y, w, h =  hist_roi
        image[y:y+h, x:x+w] = pre_img
        cv2.imshow("image", image)

coin_no = 15
image, th_img = preprocessing(coin_no)                            # 전처리 수행
circles = find_coins(th_img)                    # 객체 검출

coin_imgs = make_coin_img(image, circles)                # 동전 영상 생성
coin_hists = [calc_histo_hue(coin) for coin in coin_imgs] # 각 동전영상 히스토그램

for center, radius in circles:
    cv2.circle(image, center, radius, (0, 255, 0), 2)

cv2.imshow("image", image)
cv2.setMouseCallback("image", onMouse)
cv2.waitKey(0)