cmake_minimum_required(VERSION 3.27.4)

set(PROJECT_NAME worker_transpose_matrix)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inlcude directories
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

# Source files
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Separate executable: main
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Compile source files into a library
add_library(worker_transpose_matrix_lib ${SRC_FILES})
target_compile_options(worker_transpose_matrix_lib PUBLIC ${COMPILE_OPTS})
target_link_options(worker_transpose_matrix_lib PUBLIC ${LINK_OPTS})
#setup_warnings(worker_transpose_matrix_lib)

# Main is separate
add_executable(worker_transpose_matrix ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_compile_options(worker_transpose_matrix PRIVATE ${COMPILE_OPTS})
target_link_options(worker_transpose_matrix PRIVATE ${LINK_OPTS})
target_link_libraries(worker_transpose_matrix worker_transpose_matrix_lib)
#setup_warnings(worker_transpose_matrix)