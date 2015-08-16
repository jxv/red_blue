cmake_minimum_required(VERSION 2.8)
project(red_blue)
add_definitions("-std=c++14")
add_definitions("-D_GLIBCXX_USE_C99")
include_directories(include)
file(GLOB SRC
  "src/*.cpp"
)
file(GLOB HEADERS
  "include/*.h"
  "include/red_blue/*.h"
)

add_library(red_blue STATIC ${SRC} ${HEADERS})
