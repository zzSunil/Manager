cmake_minimum_required(VERSION 3.25)
project(Manager)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-D__DEBUG__)

include_directories(include)

file(GLOB_RECURSE SOURCE demo/demo1.cpp ./src/*.cpp ./src/*.cc)

add_executable(${PROJECT_NAME} ${SOURCE})
