# 使用说明：
1. 
终端一：
roscore
终端二：
cd your/path/to/华南虎视觉感知任务/任务3.5.2
catkin_make
source your/path/to/华南虎视觉感知任务/任务3.5.2/devel/setup.bash
roslaunch usb_cam usb_cam-test.launch(其实写了launch文件可以不需要roscore/source setup.bash命令)
2. 在your/path/to/华南虎视觉感知任务/任务3.5.2/src/usb_cam/launch/usb_camtest.launch文件中修改相机参数（注意：图像的长宽需要分别小于640/480，推荐修改比例遵循4：3）


