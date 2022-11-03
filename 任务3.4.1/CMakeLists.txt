CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT (test)
#LINK_DIRECTORIES(${M1} ${M2} ${Math})

####### 以下禁止修改 #######
add_subdirectory(common)   #
add_subdirectory(modules)  #
####### 以上禁止修改 #######

ADD_EXECUTABLE(test main.cpp)
TARGET_LINK_LIBRARIES(test A1 A2 M1 M2 Math)
target_include_directories(test PUBLIC M1 PUBLIC A1 PUBLIC A2 PUBLIC M2 PUBLIC Math )
#TARGET_LINK_LIBRARIES(task2 ${OpenCV_LIBS})
