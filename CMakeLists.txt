cmake_minimum_required(VERSION 3.16.5)
project(ThiefSTL)

# set standard with 11
set(CMAKE_CXX_STANDARD 11)

# include files
include_directories(./include/memory)

# compile test file
file(GLOB_RECURSE test_cpps ./test/*.cpp)
message(${test_cpps})
foreach(test_exe ${test_cpps})
  get_filename_component(mainname ${test_exe} NAME_WE)
  add_executable(${mainname} ${test_exe})
endforeach()
