cmake_minimum_required(VERSION 3.14)

project(rpc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(rpc_server
  server.cpp
  functions.h
  macros.h
)
add_executable(rpc_client
  client.cpp
  functions.h
  macros.h
)

include(GNUInstallDirs)
