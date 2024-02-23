cmake_minimum_required(VERSION 3.20)

project(examples CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(Lua REQUIRED)
find_package(Sol2 REQUIRED)

add_library(proto-objects OBJECT addressbook.proto)

target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf)

protobuf_generate(
    LANGUAGE cpp
    TARGET proto-objects
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}")

protobuf_generate(
    LANGUAGE lbc
    GENERATE_EXTENSIONS .pb.lbc.h
    PLUGIN "${CMAKE_CURRENT_BINARY_DIR}/../compiler/protoc-gen-lbc"
    TARGET proto-objects
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}")

add_executable(trivial trivial.cpp)

target_link_libraries(trivial PRIVATE proto-objects ${LUA_LIBRARIES})

target_include_directories(trivial PRIVATE
    ${LUA_INCLUDE_DIR}
    ${SOL2_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

add_executable(simple simple.cpp)

target_link_libraries(simple PRIVATE proto-objects ${LUA_LIBRARIES})

target_include_directories(simple PRIVATE
    ${LUA_INCLUDE_DIR}
    ${SOL2_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

