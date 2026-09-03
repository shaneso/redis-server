cmake_minimum_required(VERSION 3.15)
project(kv_store CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings
add_compile_options(-Wall -Wextra -Werror)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Server executable
add_executable(kv_store_server src/server/server.cc)

# Client executable
add_executable(kv_store_client src/server/client.cc)
