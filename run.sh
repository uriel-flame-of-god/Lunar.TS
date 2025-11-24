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
echo "[1/10] Compiling memory.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/lib/memory.cpp" \
    -o "$BUILD_DIR/memory.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[2/10] Compiling Number.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Number.cpp" \
    -o "$BUILD_DIR/Number.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[3/10] Compiling Boolean.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Boolean.cpp" \
    -o "$BUILD_DIR/Boolean.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[4/10] Compiling Array.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Array.cpp" \
    -o "$BUILD_DIR/Array.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[5/10] Compiling Char.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Char.cpp" \
    -o "$BUILD_DIR/Char.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[6/10] Compiling Strings.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Strings.cpp" \
    -o "$BUILD_DIR/Strings.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[7/10] Compiling console.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/lib/console.cpp" \
    -o "$BUILD_DIR/console.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[8/10] Compiling main.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/main.cpp" \
    -o "$BUILD_DIR/main.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[9/10] Linking executable..."
g++ -O2 -fno-exceptions \
    "$BUILD_DIR/memory.o" \
    "$BUILD_DIR/Number.o" \
    "$BUILD_DIR/Boolean.o" \
    "$BUILD_DIR/Array.o" \
    "$BUILD_DIR/Char.o" \
    "$BUILD_DIR/Strings.o" \
    "$BUILD_DIR/console.o" \
    "$BUILD_DIR/main.o" \
    -o "$OUTPUT" \
    2>&1
echo "[10/10] Running tests..."
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