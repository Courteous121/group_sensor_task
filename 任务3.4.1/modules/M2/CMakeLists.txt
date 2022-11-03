AUX_SOURCE_DIRECTORY(./src DIR_SRCS)

add_library(M2 SHARED ${DIR_SRCS})
find_package(OpenCV REQUIRED)
#link_directories(/usr/local/)
#kalman_INCLUDE_DIRS
target_link_libraries(M2 A1 A2 )
target_include_directories(M2 PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(M2 ${OpenCV_LIBS})

#target_link_libraries(M2 kalman filter include directories)
target_include_directories(M2 PUBLIC include PUBLIC ${kalman_INCLUDE_DIRS})
