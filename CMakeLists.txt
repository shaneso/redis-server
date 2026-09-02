cmake_minimum_required(VERSION 3.15)
project(kv_store CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your library
add_library(kv_store_lib 
  src/kv_store.cpp
  src/resp_parser.cpp
)

# Add executable
add_executable(kv_store_server src/main.cpp)
target_link_libraries(kv_store_server kv_store_lib)

# Add tests
enable_testing()
add_executable(kv_store_test tests/test_kv_store.cpp tests/test_resp_parser.cpp)
target_link_libraries(kv_store_test kv_store_lib)
add_test(NAME KVStoreTests COMMAND kv_store_test)
