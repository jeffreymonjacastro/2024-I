cmake_minimum_required(VERSION 3.27)
project(2024_I)

set(CMAKE_CXX_STANDARD 17)

add_executable(DB DBII/S7/avl.cpp)

add_executable(Compi
        Compi/S7/Ejercicio3-lab7/imp.hh
        Compi/S7/Ejercicio3-lab7/imp.cpp
        Compi/S7/Ejercicio3-lab7/imp_parser.hh
        Compi/S7/Ejercicio3-lab7/imp_parser.cpp
        Compi/S7/Ejercicio3-lab7/imp_printer.hh
        Compi/S7/Ejercicio3-lab7/imp_printer.cpp
        Compi/S7/Ejercicio3-lab7/imp_interpreter.hh
        Compi/S7/Ejercicio3-lab7/imp_interpreter.cpp
        Compi/S7/Ejercicio3-lab7/imp_ast_visitor.hh
        Compi/S7/Ejercicio3-lab7/imp_ast_test.cpp

)

add_executable(CPC CPC/exercises/ac/S4/A.cpp)

add_executable(ADA ADA/firstMissingNumber.cpp)