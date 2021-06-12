cmake_minimum_required(VERSION 3.19)
project(mtm_ex2)

set(CMAKE_CXX_STANDARD 11)

add_executable(mtm_ex2 examSystem/tests/main.cpp examSystem/ExamDetails.cpp examSystem/headers/ExamDetails.h
        SortedList/SortedList.cpp SortedList/headers/SortedList.h SortedList/ListNode.cpp SortedList/headers/ListNode.h)