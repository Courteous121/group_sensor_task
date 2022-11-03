cmake_minimum_required(VERSION 3.10)
project(task3.11)

add_executable(task3.11 main.cpp)

find_package(OpenCV REQUIRED)
target_include_directories(task3.11 PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(task3.11 ${OpenCV_LIBS})
