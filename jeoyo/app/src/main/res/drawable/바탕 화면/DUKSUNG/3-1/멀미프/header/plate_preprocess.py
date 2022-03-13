import numpy as np, cv2

def find_value_position(img, direct):
    project = cv2.reduce(img, direct, cv2.REDUCE_AVG).ravel()
    p0, p1 = -1, -1                                                 # 초기값
    len = project.shape[0]                                   # 전체 길이
    for i in range(len):
        if p0 < 0 and project[i] < 250: p0 = i
        if p1 < 0 and project[len-i-1] < 250 : p1 = len-i-1
    return p0, p1

def find_number(part):
    x0, x1 = find_value_position(part, 0)  # 수직 투영
    y0, y1 = find_value_position(part, 1)  # 수평 투영
    return part[y0:y1, x0:x1]

# 숫자 객체 셀 중심 배치
def place_middle(number, new_size):
    h, w = number.shape[:2]
    big = max(h, w)
    square = np.full((big, big), 255, np.float32)  # 실수 자료형

    dx, dy = np.subtract(big, (w,h))//2
    square[dy:dy + h, dx:dx + w] = number
    return cv2.resize(square, new_size).flatten()  # 크기변경 및 벡터변환 후 반환

def preprocessing(car_no):
    image = cv2.imread("images/car/%02d.jpg" % car_no, cv2.IMREAD_COLOR)
    if image is None: return None, None

    kernel = np.ones((5, 13), np.uint8)  # 닫힘 연산 마스크
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  # 명암도 영상 변환
    gray = cv2.blur(gray, (5, 5))  # 블러링
    gray = cv2.Sobel(gray, cv2.CV_8U, 1, 0, 3)  # 소벨 에지 검출

    th_img = cv2.threshold(gray, 120, 255, cv2.THRESH_BINARY)[1]  # 이진화 수행
    morph = cv2.morphologyEx(th_img, cv2.MORPH_CLOSE, kernel, iterations=3)

    # cv2.imshow("th_img", th_img); cv2.imshow("morph", morph)
    return image, morph


def verify_aspect_size(size):
    w, h = size
    if h == 0 or w == 0: return False

    aspect = h / w if h > w else w / h  # 종횡비 계산

    chk1 = 3000 < (h * w) < 12000  # 번호판 넓이 조건
    chk2 = 2.0 < aspect < 6.5  # 번호판 종횡비 조건
    return (chk1 and chk2)


def find_candidates(image):
    results = cv2.findContours(image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours = results[0] if int(cv2.__version__[0]) >= 4 else results[1]

    rects = [cv2.minAreaRect(c) for c in contours]  # 외곽 최소 영역
    candidates = [(tuple(map(int, center)), tuple(map(int, size)), angle)
                  for center, size, angle in rects if verify_aspect_size(size)]

    return candidates