cmake_minimum_required( VERSION 3.20 )
project( dot_graph_lib LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( DOT_GRAPH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

add_library( DotGraphLib INTERFACE )

target_include_directories( DotGraphLib INTERFACE ${DOT_GRAPH_INCLUDE_DIR} )
