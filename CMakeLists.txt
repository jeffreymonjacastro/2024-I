cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

#add_executable(DB DBII/S7/extendibleHashing.cpp)

add_executable(Compi
        Compi/S9/lab9.2/environment.hh
        Compi/S9/lab9.2/imp.hh
        Compi/S9/lab9.2/imp.cpp
        Compi/S9/lab9.2/imp_parser.hh
        Compi/S9/lab9.2/imp_parser.cpp
        Compi/S9/lab9.2/imp_visitor.hh
        Compi/S9/lab9.2/imp_printer.hh
        Compi/S9/lab9.2/imp_printer.cpp
        Compi/S9/lab9.2/imp_interpreter.hh
        Compi/S9/lab9.2/imp_interpreter.cpp
        Compi/S9/lab9.2/imp_value.hh
        Compi/S9/lab9.2/imp_value.cpp
        Compi/S9/lab9.2/imp_test.cpp
)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/firstMissingNumber.cpp)