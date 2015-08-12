cmake_minimum_required(VERSION 2.8)
project(RedBlue)
add_definitions("-std=c++14")
add_definitions("-D_GLIBCXX_USE_C99")
include_directories(.)
file(GLOB SRC
  "*.cpp"
  "RedBlue/*.cpp"
)
file(GLOB HEADERS
  "*.hpp"
  "RedBlue/*.hpp"
)

add_library(RedBlue STATIC ${SRC} ${HEADERS})
