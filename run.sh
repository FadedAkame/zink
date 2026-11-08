#!/usr/bin/env bash
set -e

BIN_NAME="zink"
BUILD_DIR="build"

cmake --build "$BUILD_DIR" -j"$(nproc)"
exec "$BUILD_DIR/$BIN_NAME" "$@"
