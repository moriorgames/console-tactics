cmake_minimum_required(VERSION 3.2)
project(ConsoleTactics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Setup the code coverage
if ("$ENV{DEBUG_MODE}" STREQUAL "true")
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    MESSAGE(STATUS "Executing Code Coverage...")
endif()

add_subdirectory(src)
add_subdirectory(tests)

set(SOURCE_FILES main.cpp)
add_executable(main ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main ${SFML_LIBRARIES})
endif()

target_link_libraries(main console_tactics)
