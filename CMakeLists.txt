cmake_minimum_required(VERSION 3.9)
project(Compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(Compiler
        classes/Compiler.cpp
        classes/DFA.cpp
        classes/Generator.cpp
        classes/NFA.cpp
        classes/Node.cpp
        classes/Reader2.cpp
        classes/RegexParser.cpp
        classes/Transition.cpp
        headers/DFA.h
        headers/Generator.h
        headers/NFA.h
        headers/Node.h
        headers/Reader2.h
        headers/RegexParser.h
        headers/Transition.h classes/Evaluator.cpp headers/Evaluator.h classes/Construction.cpp headers/Construction.h classes/PostfixInfix.cpp headers/PostfixInfix.h classes/OperationHandler.cpp headers/OperationHandler.h)
