cmake_minimum_required(VERSION 3.24)
project(sports_bets)

set(CMAKE_CXX_STANDARD 17)

add_executable(sports_bets Sports_Betting.cpp events.cpp events.h bets.h)
