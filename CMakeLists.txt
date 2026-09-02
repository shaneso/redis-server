cmake_minimum_required(VERSION 3.15)
project(kv_store CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Auto-discover source files (excluding executables)
file(GLOB_RECURSE LIB_SOURCES "src/**/*.cc" "src/**/*.cpp")

# Remove server executables from library
list(FILTER LIB_SOURCES EXCLUDE REGEX "src/server/(server|client)\\.cc$")

# Create library
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
