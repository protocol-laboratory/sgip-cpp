cmake_minimum_required(VERSION 3.28)
project(sgip_cpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/Cellar/asio/1.28.1/include)
include_directories(include)

add_subdirectory(include)
add_subdirectory(examples)
