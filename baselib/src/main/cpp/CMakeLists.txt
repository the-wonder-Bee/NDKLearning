cmake_minimum_required(VERSION 3.10.2)

project("baselib")

add_library(testlib SHARED test.cpp)

find_library(log-lib log)

target_link_libraries(testlib ${log-lib})