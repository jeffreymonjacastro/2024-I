cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

add_executable(DB DBII/S7/avl.cpp)

add_executable(Compi
        Compi/S7/lab6/imp.hh
        Compi/S7/lab6/imp.cpp
        Compi/S7/lab6/imp_parser.hh
        Compi/S7/lab6/imp_parser.cpp
        Compi/S7/lab6/imp_printer.hh
        Compi/S7/lab6/imp_printer.cpp
        Compi/S7/lab6/imp_interpreter.hh
        Compi/S7/lab6/imp_interpreter.cpp
        Compi/S7/lab6/environment.hh
        Compi/S7/lab6/environment.cpp
        Compi/S7/lab6/imp_visitor.hh
        Compi/S7/lab6/imp_test.cpp
#        Compi/S7/lab6/imp_memory.hh
)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/firstMissingNumber.cpp)