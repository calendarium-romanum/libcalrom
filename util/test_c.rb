# primitive test auto-discovery:
#
# goes through a series of test declarations,
# generates code registering them

puts <<EOS
// this file is generated

#include <glib.h>
#include "tests.h"

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
EOS

ARGF.each do |line|
  match = line.match(/void (?<name>test_.+?)\(.+?\)/)
  next unless match

  name = match[:name]
  segments = name.sub('test', '').gsub('_', '/')

  puts "  g_test_add_func(\"#{segments}\", #{name});"
end

puts <<EOS
  return g_test_run();
}
EOS
