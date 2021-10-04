cmake_minimum_required(VERSION 3.15)

project(protoc-gen-luabythec CXX)

find_package(Protobuf REQUIRED)
find_package(Boost REQUIRED)

add_executable(protoc-gen-luabythec 
  src/enum.cpp
  src/field.cpp
  src/file.cpp
  src/generator.cpp
  src/message.cpp
  src/utils.cpp
  src/main.cpp)

target_compile_features(protoc-gen-luabythec 
  PRIVATE 
  cxx_std_14)

target_link_libraries(protoc-gen-luabythec
  PRIVATE
  protobuf::libprotoc protobuf::libprotobuf)
