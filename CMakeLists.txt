cmake_minimum_required(VERSION 3.12.2)
project(HnJ_2ndRoad)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(HnJ_2ndRoad main.cpp server_side/Server.h server_side/ClientHandler.h server_side/MySerialServer.h server_side/MyTestClientHandler.cpp cache/FileCacheManager.h cache/ReverseFileCache.h cache/ReverseFileCache.cpp)