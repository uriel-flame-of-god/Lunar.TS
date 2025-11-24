#include "Char.hpp"
#include "lib/memory.hpp"

Char::Char(char c) : value(c) {}

Char::Char(int c) : value((char)(c & 0xFF)) {}

char Char::getValue() const {
    return value;
}

bool Char::isDigit() const {
    return value >= '0' && value <= '9';
}

bool Char::isLetter() const {
    return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

bool Char::isWhitespace() const {
    return value == ' ' || value == '\t' || value == '\n' || value == '\r';
}

bool Char::isUpperCase() const {
    return value >= 'A' && value <= 'Z';
}

bool Char::isLowerCase() const {
    return value >= 'a' && value <= 'z';
}

Char Char::toUpperCase() const {
    if (isLowerCase()) {
        return Char(value - 32);
    }
    return *this;
}

Char Char::toLowerCase() const {
    if (isUpperCase()) {
        return Char(value + 32);
    }
    return *this;
}

bool Char::equals(const Char& other) const {
    return value == other.value;
}

int Char::compare(const Char& other) const {
    if (value < other.value) return -1;
    if (value > other.value) return 1;
    return 0;
}

char* Char::toString() const {
    char* buffer = (char*)Luna::Memory::allocate(2);
    buffer[0] = value;
    buffer[1] = '\0';
    return buffer;
}

int Char::toInt() const {
    return (int)value;
}

Char Char::fromInt(int ascii_value) {
    return Char((char)(ascii_value & 0xFF));
}

Char Char::newline() {
    return Char('\n');
}

Char Char::tab() {
    return Char('\t');
}

Char Char::space() {
    return Char(' ');
}

Char Char::null() {
    return Char('\0');
}