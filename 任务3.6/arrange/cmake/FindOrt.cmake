set(ORT_ROOT_PATH "/usr/local" CACHE PATH "the path to onnxruntime")

# add the include directories path
list(APPEND Ort_INCLUDE_DIR "${ORT_ROOT_PATH}/include")
list(APPEND Ort_INCLUDE_DIR "${ORT_ROOT_PATH}/include/onnxruntime")
list(APPEND Ort_INCLUDE_DIR "${ORT_ROOT_PATH}/include/onnxruntime/core")
list(APPEND Ort_INCLUDE_DIR "${ORT_ROOT_PATH}/include/onnxruntime/core/session")
find_path(
    Ort_INCLUDE_DIR
    PATH "${Ort_INCLUDE_DIR}"
    NO_DEFAULT_PATH
)

# add libraries
find_library(
    Ort_LIB
    NAMES "libonnxruntime.so"
    PATHS "${ORT_ROOT_PATH}/lib"
    NO_DEFAULT_PATH
)

mark_as_advanced(Ort_INCLUDE_DIR Ort_LIB)

set(Ort_INCLUDE_DIRS "${Ort_INCLUDE_DIR}")
set(Ort_LIBS "${Ort_LIB}")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    Ort
    REQUIRED_VARS Ort_LIB
)
