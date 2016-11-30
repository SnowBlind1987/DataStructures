cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_FLAGS "-g -pipe -O2 -std=c++11 -lm")

add_executable(hash hash_chains.cpp)
add_executable(old old_chains.cpp)
