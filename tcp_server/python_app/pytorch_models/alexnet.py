import torch
from PIL import Image
from torchvision import transforms
import numpy as np
import cv2
import os
from .ModelWrapper import ModelWrapper

with open(os.path.join(".","pytorch_models","imagenet_classes.txt"), "r") as f:
    categories = [s.strip() for s in f.readlines()]

class AlexNet(ModelWrapper):
    def __init__(self,device = 'cpu'):
        super().__init__(repo='pytorch/vision:v0.12.0',model_name='alexnet',fpass=alexnetdetect,device=device)

def alexnetdetect(model,np_img,device='cpu'):
    # Put model into evaluation mode
    model.eval()

    # Preprocess image
    input_image = Image.fromarray(np_img)
    preprocess = transforms.Compose([
        transforms.Resize(256),
        transforms.CenterCrop(224),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])
    input_tensor = preprocess(input_image)
    input_batch = input_tensor.unsqueeze(0) # create a mini-batch as expected by the model

    # Move the input and model to GPU
    if torch.cuda.is_available():
        input_batch = input_batch.to('cuda')
        model.to('cuda')

    # Shouldn't be necessary since in eval mode?
    with torch.no_grad():
        output = model(input_batch)

    # The output has unnormalized scores. To get probabilities, you can run a softmax on it.
    probabilities = torch.nn.functional.softmax(output[0], dim=0)
    top , topcatid = torch.topk(probabilities,1)

    label = str(categories[topcatid[0]])+" "+str(int(top.item()*100))+"%"
    label_org = (int((np_img.shape[1] - np_img.shape[1]/2)-50), int(np_img.shape[0]-np_img.shape[0]/2))

    # Update image with label
    edit_image = cv2.putText(np_img, label, label_org, 
                            cv2.FONT_HERSHEY_SIMPLEX, 1.1, (255,0,0), 2) 
    edit_image = cv2.putText(edit_image,'AlexNet',(10, 50), cv2.FONT_HERSHEY_SIMPLEX,2,(255,0,0),2)

    return edit_image