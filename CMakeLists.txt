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

#googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Main is separate
add_executable(transpose ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_compile_options(transpose PRIVATE ${COMPILE_OPTS})
target_link_options(transpose PRIVATE ${LINK_OPTS})
target_link_libraries(transpose worker_transpose_matrix_lib)

enable_testing()

add_executable(
  runUnitTests
  tests/tests.cpp
)
target_link_libraries(runUnitTests GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(runUnitTests)

target_link_libraries(runUnitTests worker_transpose_matrix_lib)