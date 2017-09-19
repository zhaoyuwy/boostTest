cmake_minimum_required(VERSION 3.8)
project(boostTest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp )
#set(SOURCE_FILES main.cpp curlString.cpp)
add_executable(boostTest ${SOURCE_FILES})

#Set link library.
TARGET_LINK_LIBRARIES(boostTest pthread curl)