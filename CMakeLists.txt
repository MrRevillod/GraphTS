cmake_minimum_required(VERSION 3.27.0)
project(images VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

enable_testing()

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)


add_executable(demo ${all_SRCS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
