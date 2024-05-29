cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

#add_executable(DB DBII/S7/extendibleHashing.cpp)

add_executable(Compi
        Compi/S9/lab9.1/environment.hh
        Compi/S9/lab9.1/env_test.cpp
)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/firstMissingNumber.cpp)