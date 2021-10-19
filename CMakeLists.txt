cmake_minimum_required(VERSION 3.5)
project(zn_gestion VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_subdirectory(./libs/)
add_subdirectory(./src/)
add_subdirectory(./tests/)



