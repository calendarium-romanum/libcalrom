cmake_minimum_required (VERSION 2.6)
project (specli)

add_executable(specli main.c)
target_link_libraries(specli calrom glib-2.0)
