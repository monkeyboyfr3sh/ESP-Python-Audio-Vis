import torch.nn as nn
import torch
from torchsummary import summary

class ModelWrapper():

    def __init__(self,repo=None,model_name='No model',fpass=None,load_model=True,device='cpu'):
        self.repo = repo
        self.model_name = model_name
        self.net = None
        self.device = device

        if(self.repo!=None):
            self.in_mem = load_model
            self.net = torch.hub.load(self.repo, self.model_name, pretrained=True) if load_model else None
            self.fpass = fpass
        
    def forward(self, x):
        # Load model if it is not in memory
        if not (self.in_mem):
            self.net = torch.hub.load(self.repo, self.model_name, pretrained=True)
            self.net.to('cuda')
            self.in_mem = True
            print(self.model_name,next(self.net.parameters()).is_cuda)
        # Pass input through model forward pass function
        return self.fpass(self.net,x)
    __call__ = forward


    """
    Removes model from memory
    """
    def rm_model(self):
        if(self.net!=None):
            del self.net
            self.in_mem = False