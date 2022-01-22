cmake_minimum_required(VERSION 3.19)
project(SDL_GLExample)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "CMake build type." FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "MinSizeRel" "RelWithDebInfo" "Debug")
message("Build type ${CMAKE_BUILD_TYPE}.")


option(BUILD_FAST_MATH ON)
if(BUILD_FAST_MATH)
    add_compile_options(-ffast-math)
    message("Build with fast math.")
endif()


set(BUILD_LINKER "DEFAULT" CACHE STRING "Choose linker for building.")
set_property(CACHE BUILD_LINKER PROPERTY STRINGS "DEFAULT" "BFD" "GOLD" "LLD" "MOLD")
if (BUILD_LINKER STREQUAL "MOLD")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=mold")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=mold")
elseif (BUILD_LINKER STREQUAL "LLD")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=lld")
elseif(BUILD_LINKER STREQUAL "GOLD")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold")
elseif(BUILD_LINKER STREQUAL "BFD")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=bfd")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=bfd")
endif()
message("Build with ${BUILD_LINKER} linker.")


option(BUILD_LTO OFF)
if(BUILD_LTO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    message("Build with Interoricedural Optimization.")
endif()


file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR}/ CONFIGURE_DEPENDS 
     ${PROJECT_SOURCE_DIR}/src/*.c
     ${PROJECT_SOURCE_DIR}/src/*.cc
     ${PROJECT_SOURCE_DIR}/src/*.cpp
     ${PROJECT_SOURCE_DIR}/src/*.cxx
     ${PROJECT_SOURCE_DIR}/src/*.h
     ${PROJECT_SOURCE_DIR}/src/*.hh
     ${PROJECT_SOURCE_DIR}/src/*.hpp
     ${PROJECT_SOURCE_DIR}/src/*.hxx
)

     
find_package(SDL2 REQUIRED)
find_package(fmt REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(pong ${SOURCES})
target_link_libraries(pong ${SDL2_LIBRARIES})
target_link_libraries(pong SDL2_image)
target_link_libraries(pong SDL2_ttf)
