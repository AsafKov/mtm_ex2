cmake_minimum_required(VERSION 3.19)
project(mtm_ex2)

set(CMAKE_CXX_STANDARD 11)
set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
#Part 1
#add_executable(mtm_ex2 SortedList/SortedList.h ExamSystem/ExamDetails.h ExamSystem/ExamDetails.cpp tests/main.cpp)
#Part 2
add_executable(mtm_ex2 Part2/Auxiliaries.cpp  Part2/Character.cpp Part2/gameTest.cpp
            Part2/Medic.cpp  Part2/Sniper.cpp Part2/Soldier.cpp  Part2/Game.cpp Part2/Exceptions.cpp)