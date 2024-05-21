cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

#add_executable(DB DBII/S7/extendibleHashing.cpp)

add_executable(Compi
        Compi/S8/lab8.1/environment.cpp
        Compi/S8/lab8.1/environment.hh
        Compi/S8/lab8.1/imp.cpp
        Compi/S8/lab8.1/imp.hh
        Compi/S8/lab8.1/imp_interpreter.cpp
        Compi/S8/lab8.1/imp_interpreter.hh
        Compi/S8/lab8.1/imp_parser.cpp
        Compi/S8/lab8.1/imp_parser.hh
        Compi/S8/lab8.1/imp_printer.cpp
        Compi/S8/lab8.1/imp_printer.hh
        Compi/S8/lab8.1/imp_test.cpp
        Compi/S8/lab8.1/imp_visitor.hh
)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/firstMissingNumber.cpp)