# 使用说明
终端命令：
```bash
  mkdir build
  cd build
  cmake ..
  make -j6
  ./test
```
最后效果：
```
M1 construct
I'm M1
I'm A1
I'm A2
I'm A3
M2: I'm A2
size = 1
dis = 28.2843
M1 destruct
```

# 实现思路：
1. 在第一级cmake里面包含两个子目录，添加可执行文件test,让目标链接到 A1 A2 M1 M2 Math库，并且添加相应的头文件
2. 在module文件中，第二级cmake里面添加四个子目录
3. 在A1 A2 M1 M2四个模块中分别生成对应的库文件，并且将他们对应的头文件路径添加到库文件里面，然后链接他们所需要的库
4. 在kalman模块中运用了append链接一个include文件，没有源文件；math模块中连接一个opencv库
