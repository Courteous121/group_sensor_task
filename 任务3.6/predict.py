import torch
import torchvision.transforms as transforms
from PIL import Image

from model import FCNet


def main():
    transform = transforms.Compose(
        [
            transforms.ToTensor()
        ])

    classes = ('0', '1', '2', '3', '4', '5')

    net = FCNet()
    net.load_state_dict(torch.load('FCNet.pth'))

    im = Image.open('1.jpg')
    im = transform(im)
    im = torch.unsqueeze(im, dim=0)

    with torch.no_grad():
        outputs = net(im)
        predict = torch.max(outputs, dim=1)[1].numpy()
        print(classes[int(predict)])


if __name__ == '__main__':
    main()
