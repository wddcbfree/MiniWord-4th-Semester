cmake_minimum_required(VERSION 3.10)
project(gui_with_input_method)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(gui_with_input_method
        const_define.h
        file_process.cpp
        file_process.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        memory_new.cpp
        memory_new.h
        screen.cpp
        screen.h)
