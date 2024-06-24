cmake_minimum_required(VERSION 3.10)
project(FileComp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(OPENSSL_ROOT_DIR ${openssl_SOURCE_DIR})
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

add_library(fileutil SHARED src/file_util.cpp)
target_link_libraries(fileutil OpenSSL::SSL OpenSSL::Crypto)

add_executable(fileCompare src/main.cpp)
target_link_libraries(fileCompare fileutil)

enable_testing()
add_subdirectory(test)
