cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

add_executable(DB DBII/S7/avl.cpp)

add_executable(Compi
#        Compi/S5/lab5/prueba4.cpp
#        Compi/S5/lab5/prueba4.hh
#        Compi/S5/lab5/prueba4_parser.cpp
#        Compi/S5/lab5/prueba4_parser.hh
#        Compi/S5/lab5/prueba4_test.cpp
        Compi/S4/lab42sol.cpp
)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/firstMissingNumber.cpp)