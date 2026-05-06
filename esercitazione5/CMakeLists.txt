cmake_minimum_required(VERSION 3.10)
project(Esercitazione5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_bubblesort test_bubblesort.cpp)
add_executable(test_insertionsort test_insertionsort.cpp)
add_executable(test_selectionsort test_selectionsort.cpp)
add_executable(test_mergesort test_mergesort.cpp)
add_executable(test_quicksort test_quicksort.cpp)

add_executable(measure_sorts measure_sorts.cpp timecounter.cpp)