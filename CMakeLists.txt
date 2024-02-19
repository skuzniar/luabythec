cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

project(luabythec)

add_subdirectory(compiler)
add_subdirectory(examples)
