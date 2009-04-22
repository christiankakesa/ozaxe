#!/bin/sh
#
# ------------------------------------------------------
#  OZAXE Startup Script for Unix
# ------------------------------------------------------
#
LD_LIBRARY_PATH=./plugins:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH

exec ./ozaxe
