cmake_minimum_required(VERSION 3.20)

project(examples CXX)

find_package(Protobuf CONFIG REQUIRED)

add_library(proto-objects OBJECT addressbook.proto)

target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf)

protobuf_generate(
    LANGUAGE cpp
    TARGET proto-objects
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}")

protobuf_generate(
    LANGUAGE luabythec
    GENERATE_EXTENSIONS .luabythec.pb.h
    PLUGIN "${CMAKE_CURRENT_BINARY_DIR}/../compiler/protoc-gen-luabythec"
    TARGET proto-objects
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}")

add_executable(trivial trivial.cpp)

target_link_directories(trivial PUBLIC /usr/local/lib)

target_link_libraries(trivial PRIVATE proto-objects lua)

target_include_directories(trivial PRIVATE
    ${CMAKE_SOURCE_DIR}/opt/sol2/include
    ${CMAKE_SOURCE_DIR}/opt/lua
    ${CMAKE_CURRENT_BINARY_DIR})

add_executable(simple simple.cpp)

target_link_directories(simple PUBLIC /usr/local/lib)

target_link_libraries(simple PRIVATE proto-objects lua)

target_include_directories(simple PRIVATE
    ${CMAKE_SOURCE_DIR}/opt/sol2/include
    ${CMAKE_SOURCE_DIR}/opt/lua
    ${CMAKE_CURRENT_BINARY_DIR})

