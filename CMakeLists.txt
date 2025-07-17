cmake_minimum_required(VERSION 3.30)
project(FractalDrive)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(./Dependencies/glfw)
target_link_libraries(glfw PUBLIC -static-libstdc++ -static-libgcc -static)

add_library(glad ./Dependencies/glad/src/glad.c)
target_link_libraries(glad PUBLIC -static-libstdc++ -static-libgcc -static)

add_executable(run Source/main.cpp)
target_link_libraries(run glad glfw -static-libstdc++ -static-libgcc -static)