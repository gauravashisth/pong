cmake_minimum_required(VERSION 3.10)
project(pong)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include Raylib headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link Raylib static library
add_executable(pong src/main.cpp)
target_link_libraries(pong ${CMAKE_SOURCE_DIR}/lib/libraylib.a)

# Add system dependencies for Raylib
if (APPLE)
    target_link_libraries(pong
      "-framework OpenGL"
      "-framework Cocoa"
      "-framework IOKit"
      "-framework CoreVideo"
      "-framework ApplicationServices"
  )
elseif (UNIX)
    target_link_libraries(pong
        m pthread dl GL X11
  )
endif()
