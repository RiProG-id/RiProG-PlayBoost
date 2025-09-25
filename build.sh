#!/bin/sh
set -e

# Variables
PROJECT_ROOT=$(dirname "$(realpath "$0")")
COMPILER=clang
COMPILER_FLAGS="-O3 -flto -Wall -Wextra"
LINKER_FLAGS="-flto"
EXECUTABLE_NAME=RPB
SOURCE_FILES="main.c cmd.c apps.c optimize.c mode_check.c"

# System and architecture
if [ -f /system/build.prop ]; then
	OPERATING_SYSTEM="Android"
else
	OPERATING_SYSTEM=$(uname -s)
fi
ARCHITECTURE=$(uname -m)
echo "Building on $OPERATING_SYSTEM/$ARCHITECTURE"

# Check for required commands
echo "Checking for required commands..."
if ! command -v clang >/dev/null 2>&1; then
	echo "Error: clang is not installed" >&2
	exit 1
fi
if ! command -v strip >/dev/null 2>&1; then
	echo "Error: strip (binutils) is not installed" >&2
	exit 1
fi
if ! command -v zip >/dev/null 2>&1; then
	echo "Error: zip is not installed. Please install zip to proceed." >&2
	exit 1
fi

# Build
echo "Starting build process..."
cd "$PROJECT_ROOT/source" || exit 1
OBJECT_FILES=""
echo "Compiling source files..."
for src in $SOURCE_FILES; do OBJECT_FILES="$OBJECT_FILES ${src%.c}.o"; done
[ -f "$EXECUTABLE_NAME" ] && rm "$EXECUTABLE_NAME"
rm -f $OBJECT_FILES
for src in $SOURCE_FILES; do $COMPILER $COMPILER_FLAGS -c "$src" -o "${src%.c}.o"; done
echo "Linking object files..."
$COMPILER $LINKER_FLAGS -o "$EXECUTABLE_NAME" $OBJECT_FILES
if [ -f "$EXECUTABLE_NAME" ]; then
	echo "Stripping symbols from executable..."
	strip "$EXECUTABLE_NAME"
fi
rm -f $OBJECT_FILES

# Install
echo "Installing executable..."
mkdir -p "$PROJECT_ROOT"/module/system/bin
mv "$EXECUTABLE_NAME" "$PROJECT_ROOT"/module/system/bin

# Package
echo "Creating module package..."
cd "$PROJECT_ROOT" || exit 1
version=$(grep version= "$PROJECT_ROOT"/module/module.prop | awk -F'=' '{print $2}')
zip -r -q "$PROJECT_ROOT/RiProG-PlayBoost-$version.zip" "$PROJECT_ROOT"/module/*
rm -rf "$PROJECT_ROOT"/module/system

echo "Build complete: RiProG-PlayBoost-$version.zip"
