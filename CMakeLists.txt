cmake_minimum_required(VERSION 3.16.5)
project(ThiefSTL)

option(TEST_THIEF_STL ON)
if(TEST_THIEF_STL)
  add_definitions(-DTEST_THIEF_STL)
else(TEST_THIEF_STL)
  remove_definitions(-DTEST_THIEF_STL)
endif()

# set standard with 11
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fsanitize=address -fno-omit-frame-pointer")

# include files
include_directories(./include/)
include_directories(./include/memory)
include_directories(./include/ext)

# compile test file
file(GLOB_RECURSE test_cpps ./test/*.cpp)
message(${test_cpps})
foreach(test_exe ${test_cpps})
  get_filename_component(mainname ${test_exe} NAME_WE)
  add_executable(${mainname} ${test_exe})
endforeach()
