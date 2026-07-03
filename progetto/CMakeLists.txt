cmake_minimum_required(VERSION 3.20)
project(ProgettoCircuiti)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 REQUIRED)

add_executable(risolutore_circuiti main.cpp)
target_link_libraries(risolutore_circuiti Eigen3::Eigen)