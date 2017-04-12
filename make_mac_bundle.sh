#!/bin/bash
#
# This script will 'manually' build a loadable bundle for Mac OSX, containing
# the screensaver shared module and other required files in Mac OSX bundles.

# create the bundle directory
mkdir -p 'Hexago.saver' && \
# create the sub-directories
mkdir -p 'Hexago.saver/Contents/MacOS' && \
mkdir -p 'Hexago.saver/Contents/Resources' && \
# copy the Info.plist file
cp 'Info.plist' 'Hexago.saver/Contents/Info.plist' && \
# copy the binaries in
cp 'build/hexago-mac.so' 'Hexago.saver/Contents/MacOS/Hexago';
