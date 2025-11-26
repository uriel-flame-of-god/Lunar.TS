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
echo "[1/11] Compiling memory.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/lib/memory.cpp" \
    -o "$BUILD_DIR/memory.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[2/11] Compiling Number.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Number.cpp" \
    -o "$BUILD_DIR/Number.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[3/11] Compiling Boolean.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Boolean.cpp" \
    -o "$BUILD_DIR/Boolean.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[4/11] Compiling Array.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Array.cpp" \
    -o "$BUILD_DIR/Array.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[5/11] Compiling Char.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Char.cpp" \
    -o "$BUILD_DIR/Char.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[6/11] Compiling Strings.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/types/Strings.cpp" \
    -o "$BUILD_DIR/Strings.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[7/11] Compiling console.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/lib/console.cpp" \
    -o "$BUILD_DIR/console.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[8/11] Compiling math.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/lib/math.cpp" \
    -o "$BUILD_DIR/math.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[9/11] Compiling main.cpp..."
g++ -c -O2 -march=x86-64 -fno-exceptions \
    "$PROJECT_DIR/src/main.cpp" \
    -o "$BUILD_DIR/main.o" \
    -I"$PROJECT_DIR/src" \
    2>&1
echo "[10/11] Linking executable..."
g++ -O2 -fno-exceptions \
    "$BUILD_DIR/memory.o" \
    "$BUILD_DIR/Number.o" \
    "$BUILD_DIR/Boolean.o" \
    "$BUILD_DIR/Array.o" \
    "$BUILD_DIR/Char.o" \
    "$BUILD_DIR/Strings.o" \
    "$BUILD_DIR/console.o" \
    "$BUILD_DIR/math.o" \
    "$BUILD_DIR/main.o" \
    -o "$OUTPUT" \
    2>&1
echo "[11/11] Running tests..."
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