cmake_minimum_required (VERSION 2.6)
project (tests)

FILE(GLOB TestCFiles *_test.c)

# test auto-discovery
add_custom_command(OUTPUT tests.h COMMAND bash ../util/test_h.sh ${TestCFiles} DEPENDS ${TestCFiles} WORKING_DIRECTORY .)
add_custom_command(OUTPUT main.c COMMAND bash ../util/test_c.sh tests.h MAIN_DEPENDENCY tests.h WORKING_DIRECTORY .)

add_executable(run main.c ${TestCFiles})
target_link_libraries(run calrom glib-2.0)
