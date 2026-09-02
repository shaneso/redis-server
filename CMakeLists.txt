cmake_minimum_required(VERSION 3.15)
project(kv_store CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler warnings
add_compile_options(-Wall -Wextra -Werror)

# Source discovery - get all .cc and .cpp files recursively
file(GLOB_RECURSE ALL_SOURCES 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)

# Separate library sources from executables
set(LIB_SOURCES ${ALL_SOURCES})
list(FILTER LIB_SOURCES EXCLUDE REGEX "server\\.cc$|client\\.cc$")

# Library (all utilities, parsers, etc.)
add_library(kv_store_lib ${LIB_SOURCES})
target_include_directories(kv_store_lib PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Server executable
add_executable(kv_store_server src/server/server.cc)
target_link_libraries(kv_store_server kv_store_lib)
target_include_directories(kv_store_server PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Client executable
add_executable(kv_store_client src/server/client.cc)
target_link_libraries(kv_store_client kv_store_lib)
target_include_directories(kv_store_client PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
