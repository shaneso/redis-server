cmake_minimum_required(VERSION 3.15)
project(kv_store CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings
add_compile_options(-Wall -Wextra -Werror)

# Auto-discover source files
file(GLOB_RECURSE LIB_SOURCES "src/*.cc" "src/*.cpp")
file(GLOB_RECURSE TEST_SOURCES "tests/*.cc" "tests/*.cpp")

# Remove main executable from lib sources
list(FILTER LIB_SOURCES EXCLUDE REGEX "server\\.cc$")

# Library
add_library(kv_store_lib ${LIB_SOURCES})
target_include_directories(kv_store_lib PUBLIC include)

# Server executable
add_executable(kv_store_server src/server.cc)
target_link_libraries(kv_store_server kv_store_lib)

