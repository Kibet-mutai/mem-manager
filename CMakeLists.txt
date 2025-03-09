cmake_minimum_required(VERSION 3.30.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-ggdb")
project(mem)
#add source files
set(SOURCES src/bitmap.cpp src/bst.cpp src/mem_manage.cpp src/new_malloc.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
