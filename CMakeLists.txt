cmake_minimum_required(VERSION 3.19)
project(mtm_ex2)

set(CMAKE_CXX_STANDARD 11)

add_executable(mtm_ex2 SortedList/SortedList.h ExamSystem/ExamDetails.h ExamSystem/ExamDetails.cpp tests/main.cpp)