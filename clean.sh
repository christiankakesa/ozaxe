#!/bin/sh
## clean.sh for OZAXE in /home/christian/workspace/ozaxe/trunk
## 
## Made by Christian KAKESA
## Login   <christian@epita.fr>
## 
## Started on  Thu May 31 01:45:26 2007 Christian KAKESA
## Last update Thu May 31 01:45:57 2007 Christian KAKESA
##

find . -type f -name "*~" -exec rm -f {} \;
find . -type f -name "#*#" -exec rm -f {} \;
find . -type f -name ".sconsign.dblite" -exec rm -f {} \;
find . -type f -name "*.o" -exec rm -f {} \;
