cmake_minimum_required(VERSION 3.19)
project(mtm_ex2)

set(CMAKE_CXX_STANDARD 11)

add_executable(mtm_ex2 tests/main.cpp ExamSystem/ExamDetails.cpp ExamSystem/ExamDetails.h
        SortedList/SortedList.h tests/main.cpp)