#!/bin/bash
set -e
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$PROJECT_DIR/build"
OUTPUT="$BUILD_DIR/luna"
echo "=== Luna Build System ==="
echo "Project dir: $PROJECT_DIR"
echo "Build dir: $BUILD_DIR"
mkdir -p "$BUILD_DIR"
echo ""
echo "[1/6] Compiling memory.cpp..."
g++ -c -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/lib/memory.cpp" \
    -o "$BUILD_DIR/memory.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[2/6] Compiling Number.cpp..."
g++ -c -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Number.cpp" \
    -o "$BUILD_DIR/Number.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[3/6] Compiling Boolean.cpp..."
g++ -c -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Boolean.cpp" \
    -o "$BUILD_DIR/Boolean.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[4/6] Compiling main.cpp..."
g++ -c -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/main.cpp" \
    -o "$BUILD_DIR/main.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[5/6] Linking executable..."
g++ -fno-exceptions \
    "$BUILD_DIR/memory.o" \
    "$BUILD_DIR/Number.o" \
    "$BUILD_DIR/Boolean.o" \
    "$BUILD_DIR/main.o" \
    -o "$OUTPUT" \
    2>&1
echo "[6/6] Running tests..."
echo ""
if [ -f "$OUTPUT" ]; then
    "$OUTPUT"
    EXIT_CODE=$?
    echo ""
    echo "Exit code: $EXIT_CODE"
    exit $EXIT_CODE
else
    echo "ERROR: Binary not created at $OUTPUT"
    exit 1
fi