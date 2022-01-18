cmake_minimum_required(VERSION 3.19)
project(SDL_GLExample)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR}/ CONFIGURE_DEPENDS 
     ${PROJECT_SOURCE_DIR}/src/*.c
     ${PROJECT_SOURCE_DIR}/src/*.cc
     ${PROJECT_SOURCE_DIR}/src/*.cpp
     ${PROJECT_SOURCE_DIR}/src/*.cxx
     ${PROJECT_SOURCE_DIR}/src/*.h
     ${PROJECT_SOURCE_DIR}/src/*.hh
     ${PROJECT_SOURCE_DIR}/src/*.hpp
     ${PROJECT_SOURCE_DIR}/src/*.hxx)

find_package(SDL2 REQUIRED)
find_package(fmt REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(pong ${SOURCES})
target_link_libraries(pong ${SDL2_LIBRARIES})
target_link_libraries(pong SDL2_image)
target_link_libraries(pong SDL2_ttf)

