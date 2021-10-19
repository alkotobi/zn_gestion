cmake_minimum_required(VERSION 3.5)
project(mnlibrary_test VERSION 0.1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_SOURCES
        main.c
        mnlibrary_test.h
        mnlibrary_test.c
        testing.h
        testing.c

)
add_executable(mnlibrary_test ${PROJECT_SOURCES})
target_link_libraries(mnlibrary_test  mnlibrary )
target_include_directories(mnlibrary_test PUBLIC ../../libs/mnlibrary)