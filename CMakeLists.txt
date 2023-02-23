cmake_minimum_required(VERSION 3.1)
project(plugin_test)


add_executable(main src/main.cpp src/plugin.h)
target_link_libraries(main ${CMAKE_DL_LIBS})
add_library(plugin1 SHARED src/plugin1.cpp src/plugin.h)
add_library(plugin2 SHARED src/plugin2.cpp src/plugin.h)

