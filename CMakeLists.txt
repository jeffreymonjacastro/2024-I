cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

add_executable(DB DBII/S4/main.cpp)

add_executable(Compi
        Compi/S5/imp/imp.cpp
        Compi/S5/imp/imp.hh
        Compi/S5/imp/imp_parser.cpp
        Compi/S5/imp/imp_parser.hh
        Compi/S5/imp/imp_test.cpp
)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/MatrixMultiply.cpp)