#!/bin/bash
set -e

########################################################################
# Package the binaries built on Travis CI as an AppImage
#
# For more information, see http://appimage.org/
########################################################################
echo "Starting AppImage process"

cd "$TRAVIS_BUILD_DIR/build"
OUTDIR="$TRAVIS_BUILD_DIR/deploy"

APP="jwm-settings-manager"
# this variable is used in the sourced functions below
LOWERAPP="${APP}"
RELEASE=''
if [ -n "$TRAVIS_TAG" ]
then
  VERSION="$TRAVIS_TAG"
  RELEASE="$TRAVIS_TAG"
else
  VERSION="$TRAVIS_COMMIT"
fi
if [ -z "$RELEASE" ]
then
  RELEASE="$VERSION"
fi
APPDIR="/tmp/$APP/$APP.AppDir"
export ARCH=$(arch)

echo "Name:    $APP"
echo "Version: $VERSION"
echo "Release: $RELEASE"
echo "Arch:    $ARCH"
echo
echo "Begin AppImage building!"
make install DESTDIR="$APPDIR"

cd "$APPDIR/.."
wget -q https://github.com/probonopd/AppImages/raw/master/functions.sh -O ./functions.sh
source ./functions.sh
cd "$APPDIR"

########################################################################
# Copy in dependencies
########################################################################
echo "Copy Dependencies"
copy_deps
move_lib

########################################################################
# Delete stuff that should not go into the AppImage
########################################################################
echo "Delete dangerous libraries, and remove uneeded things"
# See https://github.com/probonopd/AppImages/blob/master/excludelist
delete_blacklisted

if [ -d usr/lib/$ARCH-linux-gnu ]
then
  mv usr/lib/$ARCH-linux-gnu/* usr/lib/
  rmdir usr/lib/$ARCH-linux-gnu
fi

rm -rf usr/include || true
rm -rf usr/lib/cmake || true
rm -rf usr/doc || true
rm -rf usr/share || true
rmdir usr/lib64 || true
rmdir usr/lib/mesa || true

find . -name *.so -or -name *.so.* -exec strip {} \;
for f in $(find . -type f -executable -exec file -- {} \; | grep ELF | cut -d: -f1); do
  strip "$f"
done

########################################################################
# Get Desktop stuff
########################################################################
echo "Setting up Desktop integration"
get_icon
get_desktop
get_desktopintegration "$APP"
fix_desktop "$APP"

########################################################################
# Now packaging AppDir as an AppImage
########################################################################

echo "Generating AppImage!"
generate_appimage
echo "All finished"
exit 0
