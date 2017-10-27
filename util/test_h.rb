# collects test from .c files, generates a single header file

require 'set'

def normalize_include(str)
  str.strip
end

def create_declaration(str)
  str.strip + ';'
end

includes = Set.new
declarations = []
# read all files specified on the command line,
# read them line by line and without caring about the current file
ARGF.each do |line|
  if line =~ /^#include/
    includes << normalize_include(line)
  elsif line =~ /^void test_.+?\(.+?\)/
    declarations << create_declaration(line)
  end
end

puts '// this file is generated'
puts
includes.each {|i| puts i }
puts
declarations.each {|d| puts d }
