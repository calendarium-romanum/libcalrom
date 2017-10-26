cmake_minimum_required (VERSION 2.6)
project (calrom)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
link_directories(${GLIB_PKG_LIBRARY_DIRS})

add_subdirectory(spec_cli)

add_library(calrom calrom.c dates.c)
install(TARGETS calrom DESTINATION lib)
install(FILES calrom.h DESTINATION include)
