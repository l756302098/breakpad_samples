cmake_minimum_required(VERSION 3.5)

# Set the project name
project (breakpad_samples)

set(CMAKE_CXX_FLAGS "-O2 -Wall -g -std=c++11")
set(CMAKE_BUILD_TYPE Release)

include_directories(
    /usr/local/include/breakpad
)

add_executable(breakpad_samples src/main.cpp)

target_link_libraries(breakpad_samples breakpad_client pthread)
