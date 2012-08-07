#####################################################################################################################
#                                             CMake ABCDictionnary file                                             #
#####################################################################################################################

cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 OLD)

project(ABCDictionnary)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

include_directories(includes)
link_directories(lib/${CMAKE_BUILD_TYPE})

file(
  GLOB_RECURSE
  library_source
  src/*
  includes/*
  )
  
file(
  GLOB_RECURSE
  example1_source
  example/*
  )

add_library(
  abcdictionnary
  SHARED
  ${library_source}
  )
  
add_executable(
  example1
  ${example1_source}
  )
  
target_link_libraries(
  example1
  abcdictionnary
  )


