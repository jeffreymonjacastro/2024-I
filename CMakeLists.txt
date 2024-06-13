cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

#add_executable(DB DBII/S7/extendibleHashing.cpp)

add_executable(Compi
        Compi/S11/proj1/environment.hh
        Compi/S11/proj1/imp.hh
        Compi/S11/proj1/imp.cpp
        Compi/S11/proj1/imp_parser.hh
        Compi/S11/proj1/imp_parser.cpp
        Compi/S11/proj1/imp_visitor.hh
        Compi/S11/proj1/imp_printer.hh
        Compi/S11/proj1/imp_printer.cpp
        Compi/S11/proj1/imp_interpreter.hh
        Compi/S11/proj1/imp_interpreter.cpp
        Compi/S11/proj1/imp_value.hh
        Compi/S11/proj1/imp_value.cpp
        Compi/S11/proj1/type_visitor.hh
        Compi/S11/proj1/imp_typechecker.hh
        Compi/S11/proj1/imp_typechecker.cpp
        Compi/S11/proj1/imp_test.cpp

)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/firstMissingNumber.cpp)