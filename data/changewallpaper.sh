#!/bin/bash

# Wallpaper Changing script
# MIT license Copyright 2014 Israel Dahl <israel@torios.org>
# Made for ToriOS

#TODO: ADD command line arguments so user can set the background directory and time to change

# Get the user's pictures directory
dir=$Home+"Pictures/"

while [ 1 ]
do
# Pick a wallpaper
wallpaper=`find "${dir}" -type f | shuf -n1`

#TODO: look for only image files, and set the file extension here and in the desktop xml file
extention = ""
changer = dir+"changer"+ extention

#TODO: symlink instead of copy
cp ${wallpaper} changer

# 5 minutes
sleep 300

done
