#CMAKE Version
cmake_minimum_required(VERSION 2.6)
project(Runestone)

SET(GCC_COMPILE_FLAGS "-std=c++11")
add_definitions(${GCC_COMPILE_FLAGS})

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# set output build directory
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)
file(GLOB SOURCES_CLIENT src/*.cpp)
set(SOURCES_CLIENT ${SOURCES_CLIENT} src/client/main_client.cpp)
file(GLOB INCLUDES include/*.h)

# Define sources and executable
set(EXECUTABLE_NAME_CLIENT "client")
add_executable(${EXECUTABLE_NAME_CLIENT} ${SOURCES_CLIENT} ${INCLUDES})

file(GLOB SOURCES_SERVER src/*.cpp)
set(SOURCES_SERVER ${SOURCES_SERVER} src/server/main_server.cpp)
set(EXECUTABLE_NAME_SERVER "server")
add_executable(${EXECUTABLE_NAME_SERVER} ${SOURCES_SERVER} ${INCLUDES})

target_link_libraries(${EXECUTABLE_NAME_CLIENT} sfml-graphics sfml-window sfml-audio sfml-network sfml-system tgui)
target_link_libraries(${EXECUTABLE_NAME_SERVER} sfml-graphics sfml-window sfml-audio sfml-network sfml-system tgui)

file(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/Resources/*)
file(COPY ${RESOURCES} DESTINATION ${CMAKE_BINARY_DIR}/Resources)
