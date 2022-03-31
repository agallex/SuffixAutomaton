cmake_minimum_required(VERSION 3.17)
project(1c)

set(CMAKE_CXX_STANDARD 20)

add_executable(1c main.cpp suffix_automaton.cpp suffix_automaton.h big_file.txt)