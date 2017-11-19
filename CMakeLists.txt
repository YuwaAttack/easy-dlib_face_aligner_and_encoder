cmake_minimum_required(VERSION 3.8)
add_compile_options(-std=c++11 -lstdc++ -fPIC -O2)

include(/Users/lando/Desktop/dlib/dlib/cmake)

INCLUDE_DIRECTORIES("/Users/lando/Desktop/dlib")
link_directories("/Users/lando/Desktop/dlib/build/dlib/")

INCLUDE_DIRECTORIES("../seeta-ctypes/jsoncpp-src-0.5.0/include")
link_directories("./")

add_library(dlib_ext SHARED dlib_ext.cpp)
target_link_libraries(dlib_ext dlib::dlib)
target_link_libraries(dlib_ext json_linux-gcc-4.2.1_libmt)

