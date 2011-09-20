cmake_minimum_required(VERSION 2.8)

project(lab01)

set(lab01_sources shell.cxx command.h command.cxx)

find_package( Boost 1.36.0 )
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(lab01 ${lab01_sources})
endif()
