cmake_minimum_required(VERSION 3.10)
project(MyRaylibGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include Raylib headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link Raylib static library
add_executable(my_game src/main.cpp)
target_link_libraries(my_game ${CMAKE_SOURCE_DIR}/lib/libraylib.a)

# Add system dependencies for Raylib
if (APPLE)
    target_link_libraries(my_game "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif (UNIX)
    target_link_libraries(my_game m pthread dl GL X11)
endif()
