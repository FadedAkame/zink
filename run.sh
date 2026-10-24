#!/usr/bin/env bash
set -e

BUILD_DIR=build
BIN="$BUILD_DIR/zink"

cmake --build "$BUILD_DIR" -j"$(nproc)"
exec "$BIN" "$@"
