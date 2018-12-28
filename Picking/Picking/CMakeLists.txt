
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Picking)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Picking MACOSX_BUNDLE Picking.cxx )
 
target_link_libraries(Picking ${VTK_LIBRARIES})
