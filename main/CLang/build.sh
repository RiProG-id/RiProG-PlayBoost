#!/bin/sh
set -e
if [ -f /system/build.prop ]; then
	OS="Android"
else
	OS=$(uname -s)
fi
ARCH=$(uname -m)
echo "Building on $OS/$ARCH"
if ! command -v clang >/dev/null 2>&1; then
	echo "Error: clang not installed" >&2
	exit 1
fi
if ! command -v strip >/dev/null 2>&1; then
	echo "Error: strip (binutils) not installed" >&2
	exit 1
fi
CC=clang
CFLAGS="-O3 -flto -Wall -Wextra"
LDFLAGS="-flto"
TARGET=RPB
SRCS="main.c cmd.c apps.c optimize.c mode_check.c"
OBJS=""
for src in $SRCS; do OBJS="$OBJS ${src%.c}.o"; done
OLDPWD=$(pwd)
cd "$(dirname "$0")" || exit 1
[ -f "$TARGET" ] && rm "$TARGET"
rm -f $OBJS
for src in $SRCS; do $CC $CFLAGS -c "$src" -o "${src%.c}.o"; done
$CC $LDFLAGS -o "$TARGET" $OBJS
[ -f "$TARGET" ] && strip "$TARGET"
rm -f $OBJS
cd "$OLDPWD" || exit 1
echo "Build complete: $TARGET"
