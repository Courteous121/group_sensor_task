# yolox全过程的实现
1. 下载yolox:
* yolox网址：https://github.com/Megvii-BaseDetection/YOLOX
* 终端执行命令：
```
git clone git@github.com:Megvii-BaseDetection/YOLOX.git
cd YOLOX
pip3 install -v -e .  # or  python3 setup.py develop
```
2. 准备数据集
* yolox要求数据集必须是coco或者voc格式，可以在网上下载或者自己使用labelme软件制作数据集
* 下载网址：https://aistudio.baidu.com/aistudio/datasetoverview/2
* 注意：coco数据集中的标注文件是json格式，而voc中是xml格式
* 数据集格式：整个voc2007文件放在Yolox/datasets文件夹下面。annotation用于存放xml格式的标签文件，JPEGimage用于存放原始图片。ImageSets/Main下的两个文件可以通过运行downloading.py文件建立。
![voc数据格式](https://img-blog.csdnimg.cn/07f3d983264d43ff8e1f1fbefff7e8eb.jpg)

3. 训练
* 在YOLOX/exps/example/yolox_voc/yolox_voc_s.py文件中修改数据集参数
* 在雷达站上（因为我的电脑只有cpu，故借助雷达站完成了任务）：运行终端命令
```
conda activate duke
cd 任务3.7/YOLOX
python ~/任务3.7/YOLOX/tools/train.py -f ~/任务3.7/YOLOX/exps/example/yolox_voc/yolox_voc_s.py -d 0 -b 12 --fp16 -o -c /home/duke/任务3.7/yolox_s.pth
```
等训练完成之后就会在YOLOX/YOLOX_outputs里面看到结果
![300轮训练完成之后的结果](https://img-blog.csdnimg.cn/f20b8896041b41208274fe0ad1e30cf3.png)

4. 将pth文件格式转为engine进行在c++上的部署
5. 修改YOLOX/DEMO/TensorRT/cpp里面yolox.cpp的参数，在终端执行命令：
```shell
mkdir build
cd build
cmake ..
make
./yolox ../model_trt.engine -i ../../../../assets/dog.jpg
```
![终端结果](https://img-blog.csdnimg.cn/fa235bf38f0b41bd894a4ef985fd99bb.png)

![预测的结果](https://img-blog.csdnimg.cn/08dadff6fcd042abad44e41719c802e9.jpeg)





