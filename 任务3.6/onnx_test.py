import onnx


model = onnx.load('FCNet.onnx')
onnx.checker.check_model(model)


