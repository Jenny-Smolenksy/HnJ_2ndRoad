cmake_minimum_required(VERSION 3.12.2)
project(HnJ_2ndRoad)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(HnJ_2ndRoad main.cpp server_side/Server.h problem_solve/Solver.h cache/FileCacheManager.h cache/FileToucher.cpp cache/FileToucher.h Utils.cpp Utils.h problem_solve/StringRevrser.h)