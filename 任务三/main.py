import os
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
# from torch.testing._internal.distributed.rpc.examples.parameter_server_test import batch_size
from torchvision import transforms
from torchvision.datasets import ImageFolder
import matplotlib.pyplot as plt


# os.path子库，操作处理文件路径
# 1.定义一个全连接网络
class FCNet(nn.Module):  # 全连接网络    `
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(480000, 512)
        self.fc2 = nn.Linear(512, 256)
        self.fc3 = nn.Linear(256, 128)
        self.fc4 = nn.Linear(128, 64)
        self.fc5 = nn.Linear(64, 10)
        self.dropout = nn.Dropout(p=0.2)

    def forward(self, x):
        x = x.view(x.shape[0], -1)
        x_1 = self.dropout(F.relu(self.fc1(x)))
        x_2 = self.dropout(F.relu(self.fc2(x_1)))
        x_3 = self.dropout(F.relu(self.fc3(x_2)))
        x_4 = self.dropout(F.relu(self.fc4(x_3)))
        x_out = F.softmax(self.fc5(x_4), 1)
        return x_out


# 2.定义图片转换方式
train_transforms = transforms.Compose([
    transforms.RandomResizedCrop(400),
    transforms.ToTensor()
])

# 3. 定义地址
path1 = os.path.join(os.getcwd(), '装甲板数字数据集', 'train')
path2 = os.path.join(os.getcwd(), '装甲板数字数据集', 'val')
# 4. 将文件夹数据导入
dataset1 = ImageFolder(path1, transform=train_transforms)

dataset2 = ImageFolder(path2, transform=train_transforms)

# 5. 将文件夹数据导入
train_loader = torch.utils.data.DataLoader(dataset1,
                                           batch_size=1, shuffle=True,
                                           num_workers=6)

val_loader = torch.utils.data.DataLoader(dataset2,
                                         batch_size=1, shuffle=True,
                                         num_workers=6)

# 6. 传入网络进行训练
net = FCNet()  # 实例化网络
lossFunc = nn.CrossEntropyLoss()  # 定义损失函数
optimizer = optim.Adam(net.parameters(), lr=0.0001)  # 定义优化器，设置学习率
epochs = 20  # 训练轮数

train_loss, test_loss = [], []

print("开始训练FCNet")
for e in range(epochs):
    running_loss = 0

    for images, labels in train_loader:  # 小批量读取数据
        optimizer.zero_grad()  # 将梯度清零
        y_hat = net(images)  # 将数据输入网络
        loss = lossFunc(y_hat, labels)  # 计算loss值
        loss.backward()  # 误差反向传播
        optimizer.step()  # 参数更新
        running_loss += loss.item()  ## 将每轮的loss求和

    test_runningloss = 0
    test_acc = 0

    with torch.no_grad():  # 验证时不记录梯度
        net.eval()  # 评估模式
        for images, labels in val_loader:
            y_hat = net(images)
            test_runningloss += lossFunc(y_hat, labels)
            ps = torch.exp(y_hat)
            top_p, top_class = ps.topk(1, dim=1)
            equals = top_class == labels.view(*top_class.shape)

            test_acc += torch.mean(equals.type(torch.FloatTensor))
    net.train()

    train_loss.append(running_loss / len(train_loader))
    test_loss.append(test_runningloss / len(val_loader))

    print("训练集学习次数: {}/{}.. ".format(e + 1, epochs),
          "训练误差: {:.3f}.. ".format(running_loss / len(train_loader)),
          "测试误差: {:.3f}.. ".format(test_runningloss / len(val_loader)),
          "模型分类准确率: {:.3f}".format(test_acc / len(val_loader)))

# 训练结果可视化
plt.plot(train_loss, label='train loss')
plt.plot(test_loss, label='test loss')
plt.legend()
plt.show()
