cmake_minimum_required(VERSION 3.7)
project(Lab_2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SOURCE_FILES main.cpp linked_list.h serial_test.h test.h mutex_test.h rw_lock_test.h)
add_executable(Lab_2 ${SOURCE_FILES})