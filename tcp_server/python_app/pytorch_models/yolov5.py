import torch
from PIL import Image
from torchvision import transforms
import numpy as np
import cv2
from .ModelWrapper import ModelWrapper

CLASS_NAMES = ['person', 'bicycle', 'car', 'motorbike', 'aeroplane', 'bus', 'train', 'truck', 'boat', 'traffic light', 'fire hydrant', 'stop sign', 'parking meter', 'bench', 'bird', 'cat', 'dog', 'horse', 'sheep', 'cow', 'elephant', 'bear', 'zebra', 'giraffe', 'backpack', 'umbrella', 'handbag', 'tie', 'suitcase', 'frisbee', 'skis', 'snowboard', 'sports ball', 'kite', 'baseball bat', 'baseball glove', 'skateboard', 'surfboard', 'tennis racket', 'bottle', 'wine glass', 'cup', 'fork', 'knife', 'spoon', 'bowl', 'banana', 'apple', 'sandwich', 'orange', 'broccoli', 'carrot', 'hot dog', 'pizza', 'donut', 'cake', 'chair', 'sofa', 'pottedplant', 'bed', 'diningtable', 'toilet', 'tvmonitor', 'laptop', 'mouse', 'remote', 'keyboard', 'cell phone', 'microwave', 'oven', 'toaster', 'sink', 'refrigerator', 'book', 'clock', 'vase', 'scissors', 'teddy bear', 'hair drier', 'toothbrush']

class YoloV5(ModelWrapper):
    def __init__(self,device = 'cpu'):
        super().__init__(repo='ultralytics/yolov5',model_name='yolov5s',fpass=self.yolov5detect,device=device)
        self.person_det = False
    def forward(self, x):
        # Load model if it is not in memory
        if not (self.in_mem):
            self.net = torch.hub.load(self.repo, self.model_name, pretrained=True)
            self.net.to('cuda')
            self.in_mem = True
            print(self.model_name,next(self.net.parameters()).is_cuda)
        # Pass input through model forward pass function
        frame = self.fpass(self.net,x)
        print('Come through here')
        return frame

    def yolov5detect(self,model,np_img,device='cpu'):
        
        output = model(np_img)
        tensor = output.xyxy[0]

        self.person_det = False
        for i in range(len(tensor)):
            b = tensor[i][:]
            if(CLASS_NAMES[int(b[5].item())]=='person'):
                self.person_det = True

            x1, y1 = (int(b[0].item()), int(b[1].item()))
            x2, y2 = (int(b[2].item()), int(b[3].item()))

            color = (255,0,0)
            thickness = 2

            np_img = cv2.rectangle(np_img,(x1, y1), (x2, y2),color, thickness)
            np_img = cv2.putText(np_img,CLASS_NAMES[int(b[5].item())],(x1, y1-10), cv2.FONT_HERSHEY_SIMPLEX,0.9,(255,0,0),2)
        
        np_img = cv2.putText(np_img,'YOLO V5',(10, 50), cv2.FONT_HERSHEY_SIMPLEX,2,(255,0,0),2)
        
        return np_img