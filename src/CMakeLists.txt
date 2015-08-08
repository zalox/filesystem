find_package(Boost 1.55 COMPONENTS system filesystem REQUIRED)

add_library(${project_name} SHARED
  filesystem.hpp
)

set_target_properties(${project_name} PROPERTIES LINKER_LANGUAGE CXX)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${project_name} ${Boost_LIBRARIES})