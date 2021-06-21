cmake_minimum_required(VERSION 3.19)
project(mtm_ex2)

set(CMAKE_CXX_STANDARD 11)
set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
#Part A
add_executable(mtm_ex2 PartA/sortedList.h PartA/ExamDetails.h PartA/ExamDetails.cpp PartA/newTest.cpp)
#Part B
#add_executable(mtm_ex2 PartB/Auxiliaries.cpp  PartB/Character.cpp PartB/Exceptions.h
#           PartB/Medic.cpp  PartB/Sniper.cpp PartB/Soldier.cpp  PartB/Game.cpp PartB/autoGameTester.cpp PartB/Exceptions.cpp)