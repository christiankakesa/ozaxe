#!/usr/bin/env ruby -w
=begin
This file is part of OZAXE project.

This class intend to be an object root of all of the classes in OZAXE 
application.

@author Christian KAKESA <christian.kakesa@gmail.com>
@copyright OZAXE-TEAM and ETNA school (c) 2008.
=end
colour_file = File.open("X11Color.h", "w")
colour_file.puts  "/*"
colour_file.puts  "** This file is part of OZAXE project."
colour_file.puts  "**"
colour_file.puts  "** This class intend to be an object root of all of the classes in OZAXE "
colour_file.puts  "** application."
colour_file.puts  "**"
colour_file.puts  "** @author Christian KAKESA <christian.kakesa@gmail.com>"
colour_file.puts  "** @copyright OZAXE-TEAM and ETNA school (c) 2008."
colour_file.puts  "*/"
colour_file.puts  ""
colour_file.puts  "#ifndef __X11COLOR_H_"
colour_file.puts  "#define __X11COLOR_H_"
colour_file.puts  ""
File.open("x11_rgb.txt").each do |line|
  colour = line.gsub(/\ +|\s+/, ' ')
  colour.gsub!(/^\ +/, '')
  colour = colour.split(/ /, 4)[3]
  colour_file.puts  "#define X11COLOR_" + colour.upcase.gsub(/^\ +/, '').gsub(/\ +$/, '').gsub(/\ /, '_') + "\t\t\t" + "(\"" + colour.downcase.gsub(/^\ +/, '').gsub(/\ +$/, '') + "\")"
end
colour_file.puts ""
colour_file.puts  "#endif /* !__X11COLOR_H_ */"
colour_file.close
