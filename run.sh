#!/usr/bin/env bash

mkdir build
cd build
# if TEST_THIEF_STL is OFF, use std c++ lib
cmake  -DTEST_THIEF_STL=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=1  ..
make
