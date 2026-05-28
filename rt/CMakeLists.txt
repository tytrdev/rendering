cmake_minimum_required(VERSION 3.12...3.26)

get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT is_multi_config AND NOT (CMAKE_BUILD_TYPE OR DEFINED ENV{CMAKE_BUILD_TYPE}))
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Release default")
endif()

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|Intel")
  add_compile_options(-Wall)
endif()

find_package(OpenMP COMPONENTS CXX)

file(GLOB CORE_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
if(CORE_SOURCES)
  add_library(rt_core STATIC ${CORE_SOURCES})
else()
  add_library(rt_core INTERFACE)
endif()

if(CORE_SOURCES)
  target_include_directories(rt_core PUBLIC ${CMAKE_SOURCE_DIR}/src)
  target_link_libraries(rt_core PUBLIC $<$<BOOL:${OpenMP_CXX_FOUND}>:OpenMP::OpenMP_CXX>)
else()
  target_include_directories(rt_core INTERFACE ${CMAKE_SOURCE_DIR}/src)
  target_link_libraries(rt_core INTERFACE $<$<BOOL:${OpenMP_CXX_FOUND}>:OpenMP::OpenMP_CXX>)
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE rt_core)

include(CTest)
if(BUILD_TESTING)
  file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/tests/*.cpp")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests/output")
  foreach(test_src IN LISTS TEST_SOURCES)
    get_filename_component(test_name "${test_src}" NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE rt_core)
    add_test(
      NAME ${test_name}
      COMMAND ${test_name}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
  endforeach()
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")
