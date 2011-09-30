cmake_minimum_required(VERSION 2.6)
project(SandboxGL)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
)

add_subdirectory(HelloGL)
add_subdirectory(Bounce)
add_subdirectory(FromScratch)
add_subdirectory(Legacy)

