cmake_minimum_required(VERSION 3.26)

add_library(stbiw STATIC stb_image_write.cpp)
target_include_directories(stbiw PUBLIC .)