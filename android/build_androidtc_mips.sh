#/bin/sh

#
# See: http://boinc.berkeley.edu/trac/wiki/AndroidBuildClient#
#

# Script to setup Android toolchain

export ANDROIDTC="$HOME/androidmips-tc"

if [ ! -d $ANDROIDTC/mipsel-linux-android ]; then
    $NDKROOT/build/tools/make-standalone-toolchain.sh --platform=android-9 --arch=mips --install-dir=$ANDROIDTC
fi
