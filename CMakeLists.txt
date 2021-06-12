cmake_minimum_required(VERSION 3.19)
project(mtm_ex2)

set(CMAKE_CXX_STANDARD 11)

add_executable(mtm_ex2 examSystem/tests/main.cpp examSystem/ExamDetails.cpp examSystem/headers/ExamDetails.h
        SortedList/SortedList.cpp SortedList/headers/SortedList.h SortedList/ListNode.cpp SortedList/headers/ListNode.h "Part B/Character.h" "Part B/Character.cpp" "Part B/Soldier.h" "Part B/Soldier.cpp" "Part B/Medic.h" "Part B/Medic.cpp" "Part B/Sniper.h" "Part B/Sniper.cpp")