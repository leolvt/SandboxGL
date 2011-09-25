cmake_minimum_required(VERSION 2.6)
project(HelloGL)

add_subdirectory(src)

install(DIRECTORY samples/ DESTINATION .)
