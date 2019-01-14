cmake_minimum_required(VERSION 3.12.2)
project(HnJ_2ndRoad)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(HnJ_2ndRoad main.cpp server_side/Server.h server_side/ClientHandler.h server_side/MySerialServer.h cache/FileCacheManager.h server_side/AServer.h server_side/AServer.cpp server_side/MySerialServer.cpp server_side/MyTestClientHandler.h cache/FileToucher.h cache/FileToucher.cpp Utils.h Utils.cpp server_side/MyClientHandler.h search/ISearchable.h search/ISearcher.h search/Searcher.h search/SolverSearcher.h search/Matrix.h search/BestFirstSearch.h search/DFS.h )