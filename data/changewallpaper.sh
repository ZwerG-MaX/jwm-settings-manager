#!/bin/bash

# Wallpaper Changing script
# MIT license Copyright 2014 Israel Dahl <israel@torios.org>
# Made for ToriOS

bglist="$HOME/.config/backgrounds"
echo "" > "$bglist"
dir="$HOME/Pictures"
# Make sure this computer has a Pictures directory
if [ ! -d "$dir" ]
then
  dir="$HOME"
fi
#get the computers primary display size
WIDTH=$(xrandr | grep primary | sed 's/.*primary//'|sed 's/+.*//'|sed 's/x.*//')
HEIGHT=$(xrandr | grep primary | sed 's/.*primary//'|sed 's/+.*//'|sed "s/${WIDTH}x//")
SVG="<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">
  <image width=\"$WIDTH\" height=\"$HEIGHT\" xlink:href=\"${IMAGE}\" />
</svg>
"
#  <rect width=\"$WIDTH\" height=\"$HEIGHT\" fill=\"rgb(0, 0, 0)\" stroke-width=\"0\" stroke=\"rgb(0, 0, 0)\" />

#DISPLAY_SIZE=$(xrandr | grep primary | sed 's/.*primary//'|sed 's/+.*//')
# make sure there is a default directory set to CURRENTDIR
CURRENTDIR="$dir"

## use this eventually to check filename age...
#DAYOLD=$(( ($(date +%s) - $(stat -L --format %Y $bglist)) > (30*60*24) ))

usage(){
echo -e '
            /*
           //
      /\  //
    ^/ \//
   ^/    = \
  ^/     @  \
 ^/          \
^/            \
/       \      \
       / \  \  o\
      /   \__\__|
      |

changewallpaper.sh [OPTIONS] [image directory]

OPTIONS
 --help (you found this one already)
  -R (all subirectories)
'
exit
}
recursive(){
  OLDIFS="$IFS"
  IFS=$'\n'
  cd "$dir"
  SUBDIRS=($(ls -d ./*/))
  cd -

  for directory in "${SUBDIRS[@]}"
  do
  
    CURRENTDIR="$dir/$directory"
#    echo $CURRENTDIR
    for jpg in "${CURRENTDIR}"*.jpg
    do
      echo "$jpg" >> "$bglist"
    done
    for JPG in "${CURRENTDIR}"*.JPG
    do
      echo "$JPG" >> "$bglist"
    done
    for png in "${CURRENTDIR}"*.png
    do
      echo "$png" >> "$bglist"
    done
    for PNG in "${CURRENTDIR}"*.PNG
    do
      echo "$PNG" >> "$bglist"
    done
  
  sed -i "s|$CURRENTDIR/\*.JPG||" "$bglist"
  sed -i "s|$CURRENTDIR/\*.jpg||" "$bglist"
  sed -i "s|$CURRENTDIR/\*.png||" "$bglist"
  sed -i "s|$CURRENTDIR/\*.PNG||" "$bglist"
  done
  IFS="$OLDIFS"
  changeWallpaper
}
singledir(){
  CURRENTDIR="$dir"
  #echo $CURRENTDIR
  for jpg in "${CURRENTDIR}"*.jpg
  do
    echo "$jpg" >> "$bglist"
  done
  for JPG in "${CURRENTDIR}"*.JPG
  do
    echo "$JPG" >> "$bglist"
  done
  for png in "${CURRENTDIR}"*.png
  do
    echo "$png" >> "$bglist"
  done
  for PNG in "${CURRENTDIR}"*.PNG
  do
    echo "$PNG" >> "$bglist"
  done  
  sed -i "s|$CURRENTDIR/\*.JPG||" "$bglist"
  sed -i "s|$CURRENTDIR/\*.jpg||" "$bglist"
  sed -i "s|$CURRENTDIR/\*.png||" "$bglist"
  sed -i "s|$CURRENTDIR/\*.PNG||" "$bglist"
  changeWallpaper
}

changeWallpaper(){
BG=($(cat "$bglist"))
for i in "${BG[@]}"
do
  IMAGE=$i
  SVG="<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">
  <image width=\"$WIDTH\" height=\"$HEIGHT\" xlink:href=\"${IMAGE}\" />
</svg>
"
echo "$SVG"


  exit
done
}
if [ "$1" == "--help" ]
then
 usage
fi
if [ "$2" != "" ]
then
  if [ -d "$2" ]
  then
   dir="$2"
  else
   echo "You need to use the full path to the directory"
    exit 1
  fi
fi

if [ "$1" == "-R" ]
then
 recursive
fi

if [ "$1" != "" ]
then
  if [ -d "$1" ]
  then
    dir="$1"
    singledir
  else
   echo "You need to use the full path to the directory"
    exit
  fi
fi

singledir

#cat "$bglist"
# 5 minutes
#sleep 300

