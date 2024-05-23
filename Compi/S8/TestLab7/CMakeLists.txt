cmake_minimum_required(VERSION 3.23)
project(lab8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab8
        environment.cpp
        environment.hh
        imp.cpp
        imp.hh
        imp_interpreter.cpp
        imp_interpreter.hh
        imp_parser.cpp
        imp_parser.hh
        imp_printer.cpp
        imp_printer.hh
        imp_test.cpp
        imp_visitor.hh)
