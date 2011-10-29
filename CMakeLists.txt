project(ships)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
include_directories ("${PROJECT_BINARY_DIR}")
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/GameBase")
add_subdirectory(GameBase)

set ( EXTRA_LIBS ${EXTRA_LIBS} GameBase)

add_executable(ships main.cpp)
target_link_libraries(ships ${QT_QTCORE_LIBRARY}  ${EXTRA_LIBS})
