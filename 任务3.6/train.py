from model import FCNet
import os
import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import transforms
from torchvision.datasets import ImageFolder




def main():
    path1 = os.path.join(os.getcwd(), '装甲板数字数据集', 'train')
    path2 = os.path.join(os.getcwd(), '装甲板数字数据集', 'val')

    transform1 = transforms.Compose(
        [
            transforms.ToTensor()
        ])

    # 4. 将文件夹数据导入
    dataset1 = ImageFolder(path1, transform=transform1)

    dataset2 = ImageFolder(path2, transform=transform1)

    # 5. 将文件夹数据导入
    train_loader = torch.utils.data.DataLoader(dataset1,
                                               batch_size=100, shuffle=True,
                                               num_workers=6)

    val_loader = torch.utils.data.DataLoader(dataset2,
                                             batch_size=100, shuffle=True,
                                             num_workers=6)

    # 6. 传入网络进行训练
    net = FCNet()  # 实例化网络
    lossFunc = nn.CrossEntropyLoss()  # 定义损失函数
    optimizer = optim.Adam(net.parameters(), lr=0.0001)  # 定义优化器，设置学习率
    epochs = 5  # 训练轮数

    train_loss, test_loss = [], []

    print("开始训练FCNet")
    for e in range(epochs):
        running_loss = 0

        for images, labels in train_loader:  # 小批量读取数据
            optimizer.zero_grad()  # 将梯度清零
            # print(images.shape)
            y_hat = net(images)  # 将训练集数据输入网络
            loss = lossFunc(y_hat, labels)  # 计算loss值
            loss.backward()  # 误差反向传播
            optimizer.step()  # 参数更新，优化参数
            running_loss += loss.item()  # 将每轮的loss求和

        test_runningloss = 0
        test_acc = 0

        with torch.no_grad():  # 验证时不记录梯度
            net.eval()  # 评估模式，使用在训练阶段学出的mean,var值

        for images, labels in val_loader:
            y_hat = net(images)
            test_runningloss += lossFunc(y_hat, labels)
            ps = torch.exp(y_hat)  # e的y_hat次方
            top_p, top_class = ps.topk(1, dim=1)  # top_p是最值，top_class是索引
            equals = (top_class == labels.view(*top_class.shape))  # equals是1或者0
            test_acc += torch.mean(equals.type(torch.FloatTensor))  # 对torch.tensor取均值；torch.floattensor是对list,numpy进行类型转换

            net.train()  # 训练模式需要

            train_loss.append(running_loss / len(train_loader))
            test_loss.append(test_runningloss / len(val_loader))

        print("训练集学习次数: {}/{}.. ".format(e + 1, epochs),
              "训练误差: {:.3f}.. ".format(running_loss / len(train_loader)),
              "验证误差: {:.3f}.. ".format(test_runningloss / len(val_loader)),
              "模型分类准确率: {:.3f}".format(test_acc / len(val_loader)))

    save_path = './FCNet.pth'
    torch.save(net, save_path)


if __name__ == '__main__':
    main()
