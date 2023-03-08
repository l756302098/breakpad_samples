cmake_minimum_required(VERSION 3.5)

# Set the project name
project (breakpad_samples)

set(CMAKE_CXX_FLAGS "-O2 -Wall -g -std=c++11")
set(CMAKE_BUILD_TYPE Release)

include_directories(
    /usr/local/include/breakpad
)

add_library(mymath SHARED
    src/math.cpp
)

add_executable(breakpad_samples src/main.cpp)

target_link_libraries(breakpad_samples breakpad_client pthread glog)

add_executable(breakpad_app src/app.cpp)

target_link_libraries(breakpad_app breakpad_client pthread glog /home/li/workspaces/breakpad_samples/build/libmymath.so)
