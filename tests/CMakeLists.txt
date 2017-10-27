cmake_minimum_required (VERSION 2.6)
project (tests)

FILE(GLOB TestCFiles *_test.c)

# test auto-discovery
execute_process(COMMAND ruby util/test_h.rb ${TestCFiles} OUTPUT_FILE tests/tests.h)
execute_process(COMMAND ruby util/test_c.rb tests/tests.h OUTPUT_FILE tests/main.c)

add_executable(run main.c ${TestCFiles})
target_link_libraries(run calrom glib-2.0)
