cmake_minimum_required(VERSION 3.17)
project(lab3_dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories("Header Files")

add_executable(lab3_dsa
        "Header Files/ExtendedTest.h"
        "Header Files/ListIterator.h"
        "Header Files/ShortTest.h"
        "Header Files/SortedIteratedList.h"
        "Source Files/App.cpp"
        "Source Files/ExtendedTest.cpp"
        "Source Files/ListIterator.cpp"
        "Source Files/ShortTest.cpp"
        "Source Files/SortedIteratedList.cpp")
