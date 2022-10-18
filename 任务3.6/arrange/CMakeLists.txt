cmake_minimum_required(VERSION 2.8)
project(Test)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#find the opencv and the qt5
find_package(OpenCV REQUIRED)
find_package(Ort REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${Ort_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS} ${Ort_LIBS}
)



