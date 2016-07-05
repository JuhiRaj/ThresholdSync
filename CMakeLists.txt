cmake_minimum_required(VERSION 2.6)
project(thresholdsync)

add_executable(thresholdsync main.cpp)

install(TARGETS thresholdsync RUNTIME DESTINATION bin)
