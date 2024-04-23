cmake_minimum_required(VERSION 3.27)
project(CancerIncidence)

set(CMAKE_CXX_STANDARD 17)

add_executable(CancerIncidence main.cpp
        StatesGraph.h
        StatesGraph.cpp
        DataSets.h
        DataSets.cpp)
