cmake_minimum_required(VERSION 3.30.0)

project(My_great_metro)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(container)
add_subdirectory(interface)
add_subdirectory(line)
add_subdirectory(Metro_system)
add_subdirectory(Stations)
add_subdirectory(tests)