cmake_minimum_required(VERSION 3.26)
project(lab3sem3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3sem3 main.cpp
        IDictionary.h
        Sequence.h
        DynamicArray.h
        DynamicArray.cpp
        Tuple.h
        ArraySequence.h
        ArraySequence.cpp
        Person.h)
