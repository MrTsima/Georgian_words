cmake_minimum_required(VERSION 3.25)
project(Georgian_words)

set(CMAKE_CXX_STANDARD 17)

add_executable(Georgian_words main.cpp txtSrapper.cpp txtSrapper.h sources.cpp sources.h)
target_link_libraries(Georgian_words poppler-cpp)


