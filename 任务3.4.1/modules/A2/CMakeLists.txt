
AUX_SOURCE_DIRECTORY(./src DIR_SRCS)

add_library(A2 SHARED ${DIR_SRCS})

target_include_directories(A2 PUBLIC include)