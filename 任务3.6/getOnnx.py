import torch
import torch.nn
import getOnnx
from model import FCNet

device = torch.device('cpu')
model = torch.load('FCNet.pth', map_location='cpu')
model.eval()

input_names = ['input']
output_names = ['output']

x = torch.randn(1, 3, 80, 80, device=device)
torch.onnx.export(model, x, 'FCNet.onnx', input_names=input_names, output_names=output_names, verbose='True')

