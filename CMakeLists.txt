cmake_minimum_required(VERSION 3.15)

project(Super-Simple-Snake-Game)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Super-Simple-Snake-Game "Snake Game/MainApp.cpp")

