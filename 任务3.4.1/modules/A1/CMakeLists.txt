AUX_SOURCE_DIRECTORY(./src DIR_SRCS)


add_library(A1 SHARED ${DIR_SRCS})

target_include_directories(A1 PUBLIC include)


