cmake_minimum_required(VERSION 3.10.2)

project(final)
include_directories(/usr/include/readline)
set(SOURCE main.cpp)

add_executable(main ${SOURCE})
target_link_libraries(main readline)

