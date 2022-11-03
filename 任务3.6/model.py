import torch.nn as nn
import torch.nn.functional as F


class FCNet(nn.Module):  # 全连接网络    `
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(19200, 512) # 80 * 80 * 3的图片输入
        self.fc2 = nn.Linear(512, 256)
        self.fc3 = nn.Linear(256, 128)
        self.fc4 = nn.Linear(128, 64)
        self.fc5 = nn.Linear(64, 6)  # 输出六个索引值
        self.dropout = nn.Dropout(p=0.2)

    def forward(self, x):
        x = x.view(x.shape[0], -1)
        x_1 = self.dropout(F.relu(self.fc1(x)))
        x_2 = self.dropout(F.relu(self.fc2(x_1)))
        x_3 = self.dropout(F.relu(self.fc3(x_2)))
        x_4 = self.dropout(F.relu(self.fc4(x_3)))
        x_out = F.softmax(self.fc5(x_4), 1)
        return x_out
