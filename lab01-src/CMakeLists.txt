cmake_minimum_required(VERSION 2.8)

project(lab01)

set(lab01_sources shell.cxx command.h command.cxx)
include_directories(/path/to/boost)
add_executable(lab01 ${lab01_sources})
