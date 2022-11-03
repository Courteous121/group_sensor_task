# 使用说明：
1. 在终端.bashrc中添加命令：
source your/path/to/任务3.5.2V2/devel/setup.bash
2. 进入“任务3.5.2V2”文件打开终端输入命令
catkin_make
roslaunch camera camera.launch


# 思路：
有一个发布节点，一个订阅节点；发布节点读取摄像头并对摄像头画面进行resize处理（方便使用launch文件夹传参数），订阅节点显示摄像头的画面
在功能包中写一个launch文件，把图片长宽的参数传进去并且运行节点。则在launch里面修改图片参数就可以。
# 遇到的问题：
1. CMakeLists中find package的时候在找catkin组合包的时候不能把opencv家加在里面，会引起错误，需要另起一行重新find packge(opencv required)
2. 没写launch文件的时候使用rosrun运行节点老是会出错，这时需要删除devel/build文件重新进行catkin_make


