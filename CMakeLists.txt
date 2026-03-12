cmake_minimum_required( VERSION 3.20 )
project( dot_graph_lib LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( SOURCES_DIR "sources" )
set( INCLUDE_DIR "include" )

set( DOT_GRAPH_SOURCES_DIR "${SOURCES_DIR}/dot_graph" )
set( DOT_GRAPH_INCLUDE_DIR "${INCLUDE_DIR}/dot_graph" )

file(
    GLOB_RECURSE
    DOT_GRAPH_SOURCES
    ${DOT_GRAPH_SOURCES_DIR}/*.cpp
)

add_library(
    DotGraphLib
    SHARED
    ${DOT_GRAPH_SOURCES}
)

target_include_directories( DotGraphLib PUBLIC ${INCLUDE_DIR} )

install(
    TARGETS DotGraphLib
    LIBRARY DESTINATION lib
)
