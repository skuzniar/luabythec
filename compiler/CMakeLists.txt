cmake_minimum_required(VERSION 3.20)

project(protoc-gen-lbc CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
find_package(Boost REQUIRED)
find_package(absl REQUIRED)

add_executable(protoc-gen-lbc 
  enum.cpp
  field.cpp
  file.cpp
  generator.cpp
  message.cpp
  utils.cpp
  main.cpp)

target_link_libraries(protoc-gen-lbc PRIVATE
  protobuf::libprotoc protobuf::libprotobuf absl::log_internal_check_op)

