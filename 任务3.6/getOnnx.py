import torch
import torch.nn
import getOnnx
from model import FCNet

device = torch.device('cpu')
model_test = FCNet();
model = torch.load('FCNet0.pth', map_location='cpu')
model_test.load_state_dict(model)
model_test.eval()

input_names = ['input']
output_names = ['output']

x = torch.randn(1, 3, 80, 80, device=device)
torch.onnx.export(model_test, x, 'FCNet2.onnx', input_names=input_names, output_names=output_names, verbose='True')
