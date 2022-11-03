import os
import random

from shutil import rmtree, copy


def mk_file(file_path: str):
    if os.path.exists(file_path):
        # 如果文件夹存在，则先删除原文件夹在重新创建
        rmtree(file_path)
    os.makedirs(file_path)

def main():
    # 保证随机可复现
    random.seed(0)

    # 将数据集中20%的数据划分到验证集中
    split_rate = 0.2# **在此处修改想要验证集数量**

    # 指向你解压后的flower_photos文件夹
    cwd = os.getcwd()# **os.getcwd()获得当前路径**
    data_root = os.path.join(cwd, "装甲板数字数据集")# **在此处修改存放数据集文件夹名称，拼接文件路径**
    origin_zjb_path = os.path.join(data_root, "zjb_photos")# **在此处修改存放未划分数据集文件夹名称**
    assert os.path.exists(origin_zjb_path), "path '{}' does not exist.".format(origin_zjb_path)
    #检查是否存在origin_flower_path目录，不符合就终止程序，输出path ’地址’ does not exist


    zjb_class = [cla for cla in os.listdir(origin_zjb_path)
                    if os.path.isdir(os.path.join(origin_zjb_path, cla))]# **在此处修改存放分类数据集名称名称flower_class**
#以origin_zjb_path文件目录下的文件名顺序建立列表,os.listdir()得到路径下的所有文件并返回以列表形式，并判断他是否是一个目录
    # 建立保存训练集的文件夹
    train_root = os.path.join(data_root, "train")
    mk_file(train_root)#判断文件夹是否存在
    for cla in zjb_class:
        # 建立每个类别对应的文件夹
        mk_file(os.path.join(train_root, cla))

    # 建立保存验证集的文件夹
    val_root = os.path.join(data_root, "val")
    mk_file(val_root)
    for cla in zjb_class:
        # 建立每个类别对应的文件夹
        mk_file(os.path.join(val_root, cla))

    for cla in zjb_class:
        cla_path = os.path.join(origin_zjb_path, cla)
        images = os.listdir(cla_path)
        num = len(images)
        # 随机采样验证集的索引
        eval_index = random.sample(images, k=int(num*split_rate))
        for index, image in enumerate(images):
            if image in eval_index:
                # 将分配至验证集中的文件复制到相应目录
                image_path = os.path.join(cla_path, image)
                new_path = os.path.join(val_root, cla)
                copy(image_path, new_path)
            else:
                # 将分配至训练集中的文件复制到相应目录
                image_path = os.path.join(cla_path, image)
                new_path = os.path.join(train_root, cla)
                copy(image_path, new_path)
            print("\r[{}] processing [{}/{}]".format(cla, index+1, num), end="")  # processing bar
        print()

    print("processing done!")


if __name__ == '__main__':
    main()
