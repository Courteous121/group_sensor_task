

AUX_SOURCE_DIRECTORY(./src DIR_SRCS)


add_library(M1 SHARED ${DIR_SRCS})

target_include_directories(M1 PUBLIC include)
target_link_libraries(M1 A1)