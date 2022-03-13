from coin_preprocess import *
from coin_utils import *                            # 기타 함수
from Common.histogram import draw_histo_hue
import matplotlib.pyplot as plt

no, max_no = 50, 100

while True:
    gray, image = preprocessing(no)                             # 전처리 수행
    if image is None:
        print("{0:02d}.jpg: 영상 파일이 없습니다.".format(no))
        if no < 0 : no: no = max_no
        no = no + 1
        if no >= max_no: no = 0
        continue

    image, th_img = preprocessing(no)                            # 전처리 수행
    circles = find_coins(th_img)                     # 객체(회전사각형) 검출
    coin_imgs = make_coin_img(image, circles)                # 동전 영상 생성
    coin_hists = [calc_histo_hue(coin) for coin in coin_imgs] # 영상 히스토그램

    merge = np.zeros((200, 456, 3), np.uint8)
    n = int(np.ceil(len(coin_imgs)/4))
    merges = cv2.repeat(merge, n, 4)
    for i, img in enumerate(coin_imgs):
        hist_img = draw_histo_hue(coin_hists[i], (200, 256, 3))    # 색상 히스토그램 표시
        h, w = hist_img.shape[:2]
        merge[:, :w] = hist_img
        merge[:, w:] = cv2.resize(img, (h, h))
        x, y = i%4 , i//4
        y, x = np.multiply( (y, x), merge.shape[:2])
        merges[y:y+h, x:x+w+200] = merge

    cv2.imshow("hist- "+ str(no) ,merges)
    cv2.moveWindow("hist- "+ str(no), -2000,400)

    key = cv2.waitKeyEx(0)  # 키 이벤트 대기
    cv2.destroyAllWindows()
    if key == 2621440:
        no = no + 1  # 아래쪽 화살표 키이면 다음 영상
    elif key == 2490368:
        no = no - 1  # 윗쪽 화살표 키이면 이전 영상
    elif key == 32 or key == 27:
        break  # 프로그램 종료 조건