import cv2
import numpy as np
import pafy
from PIL import ImageFont, ImageDraw, Image

classes = []
with open("./dnn/coco_k.names", "rt", encoding="UTF8") as f:
    classes = [line.strip() for line in f.readlines()]
    colors = np.random.uniform(0, 255, size=(len(classes), 3))
# 실습
model = cv2.dnn.readNet("./dnn/yolov3.weights", "./dnn/yolov3.cfg")
layer_names = model.getLayerNames()
output_layers = [layer_names[i[0] -1] for i in model.getUnconnectedOutLayers()]

CONF_THR = 0.5


font = ImageFont.truetype("fonts/gulim.ttc", 20)

# 20190969 박고은

url = 'https://www.youtube.com/watch?v=Q1iyBo-sewE&t=431s'
video = pafy.new(url)
best = video.getbest(preftype='mp4')
cap = cv2.VideoCapture(best.url)
if not cap.isOpened(): raise Exception("동영상파일 개방 안됨")

while True:
    ret, frame = cap.read()
    if not ret: break

    # 프레임을 모델에 넣기위해 전처리
    blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
    # 모델에 넣어주기
    model.setInput(blob)
    #결과 받아오기
    output = model.forward(output_layers)

    #주어진 이미지의 크기는 실행 속도에 영향을 미치므로 크기를 줄여서 진행
    h, w = frame.shape[0:2]
    img = cv2.resize(frame, dsize = (int(frame.shape[1] / 2), int(frame.shape[0]/2)))
    ih = int(h/2)
    iw = int(w/2)

    class_ids= []
    confidences =[]
    boxes = []

    for out in output:
        for detection in out: #각각의 물체에 대해 처리
            scores = detection[5:]
            class_id = np.argmax(scores)
            conf = scores[class_id] #확률값

            if conf > CONF_THR: #확률값이 일정값을 넘는 경우
                center_x=int(detection[0] * iw)
                center_y = int(detection[1]*ih)
                w = int(detection[2]*iw)
                h = int(detection[3]*ih)
                x = int(center_x-w/2)
                y=int(center_y-h/2)

                #각각의 박스에 대한 정보 저장
                boxes.append([x,y,w,h]) 
                confidences.append(float(conf))
                class_ids.append(class_id)
                
    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)

    for i in range(len(boxes)): 
        if i in indexes: #인덱스에 남아있는 박스들을 표시해준다
            x, y, w, h = boxes[i]
            label = str(classes[class_ids[i]])
            color = colors[i]
            conf = confidences[i]
            # 네모로 물체를 표시
            cv2.rectangle(img, (x,y), (x+w, y+h), color, 2)
            #cv2.putText(img, '{}: {: 2f}'.format(label, conf), (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1, color, 2)
            # 물체가 무엇인지 표시
            img_pil = Image.fromarray(img)
            draw = ImageDraw.Draw(img_pil)
            draw.text((x, y - 30), '{}: {:.2f}'.format(label, conf), font=font, fill=(0, 255, 0))
            img = np.array(img_pil)


    cv2.imshow('frame', img)

    #cv2.imshow('frame', frame)
    key = cv2.waitKey(3)
    if key == 27: break

cv2.destroyAllWindows()
