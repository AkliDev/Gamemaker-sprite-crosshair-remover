cmake_minimum_required(VERSION 3.22)

# set the project name
project(CrosshairDestroyer VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#submodule dependencies
add_subdirectory(CrosshairDestroyer)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CrosshairDestroyer)

