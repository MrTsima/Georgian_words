cmake_minimum_required(VERSION 3.25)
project(Georgian_words)

set(CMAKE_CXX_STANDARD 17)

# Find the Qt5 package and required modules.
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Georgian_words main.cpp txtSrapper.cpp txtSrapper.h sources.cpp sources.h)

# Link the required Qt modules to your executable.
target_link_libraries(Georgian_words PRIVATE Qt5::Widgets)

# target_link_libraries(Georgian_words PRIVATE poppler-cpp)
