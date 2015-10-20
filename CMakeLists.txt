#CMAKE Version
cmake_minimum_required(VERSION 2.6)
project(Runestone)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# set output build directory
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SFML_INCLUDE_DIR ${SFML_ROOT}/include)
set(CMAKE_PREFIX_PATH ${SFML_ROOT}/lib)

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


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME_CLIENT} ${SFML_LIBRARIES})
  target_link_libraries(${EXECUTABLE_NAME_SERVER} ${SFML_LIBRARIES})
endif()

# Add SFGUI
set(TGUI_INCLUDE_DIR ${TGUI_ROOT}/include)
set(TGUI_LIB_DIR ${TGUI_ROOT}/lib)
set(TGUI_RELEASE_LIB optimized ${TGUI_LIB_DIR}/tgui.lib)
set(TGUI_DEBUG_LIB debug ${TGUI_LIB_DIR}/tgui-d.lib)

include_directories(${TGUI_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME_CLIENT} ${TGUI_DEBUG_LIB})
target_link_libraries(${EXECUTABLE_NAME_SERVER} ${TGUI_DEBUG_LIB})
target_link_libraries(${EXECUTABLE_NAME_CLIENT} ${TGUI_RELEASE_LIB})
target_link_libraries(${EXECUTABLE_NAME_SERVER} ${TGUI_RELEASE_LIB})

file(COPY ${TGUI_LIB_DIR}/tgui.dll DESTINATION ${CMAKE_BINARY_DIR}/dlls)
file(COPY ${TGUI_LIB_DIR}/tgui-d.dll DESTINATION ${CMAKE_BINARY_DIR}/dlls)

file(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/Resources/*)
file(COPY ${RESOURCES} DESTINATION ${CMAKE_BINARY_DIR}/Resources)
file(GLOB DLLS ${SFML_ROOT}/bin/*)
file(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR}/dlls)