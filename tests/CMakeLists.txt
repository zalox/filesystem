find_package(Boost 1.55 COMPONENTS system unit_test_framework filesystem REQUIRED)

set(tests "${project_name}_tests")

add_executable(${tests}
  filesystem.cpp
)

set_target_properties(${tests} PROPERTIES LINKER_LANGUAGE CXX)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${tests} ${Boost_LIBRARIES} ${project_name})