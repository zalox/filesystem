cmake_minimum_required (VERSION 3.1)
set(project_name filesystem)
project (${project_name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


add_subdirectory(src)
add_subdirectory(tests)
