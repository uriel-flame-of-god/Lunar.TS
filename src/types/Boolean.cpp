#include "Boolean.hpp"
#include "lib/memory.hpp"

extern "C" void* luna_malloc(unsigned long size);
extern "C" void luna_free(void* ptr);

Boolean::Boolean(bool value) : value(value ? 1 : 0) {}

Boolean Boolean::logicalAnd(const Boolean& other) const {
    bool result;
    __asm__ volatile (
        "andb %2, %0"
        : "=r" (result)
        : "0" (value), "r" (other.value)
    );
    return Boolean(result);
}

Boolean Boolean::logicalOr(const Boolean& other) const {
    bool result;
    __asm__ volatile (
        "orb %2, %0"
        : "=r" (result)
        : "0" (value), "r" (other.value)
    );
    return Boolean(result);
}

Boolean Boolean::logicalNot() const {
    bool result;
    __asm__ volatile (
        "xorb $1, %0"
        : "=r" (result)
        : "0" (value)
    );
    return Boolean(result);
}

bool Boolean::equals(const Boolean& other) const {
    uint8_t result;
    __asm__ volatile (
        "cmpb %2, %1\n"
        "sete %0\n"
        : "=r" (result)
        : "r" (value), "r" (other.value)
    );
    return result != 0;
}

char* Boolean::toString() const {
    char* buffer = (char*)luna_malloc(6); // "true" or "false" + null terminator
    
    if (value) {
        buffer[0] = 'T';
        buffer[1] = 'r';
        buffer[2] = 'u';
        buffer[3] = 'e';
        buffer[4] = '\0';
    } else {
        buffer[0] = 'F';
        buffer[1] = 'a';
        buffer[2] = 'l';
        buffer[3] = 's';
        buffer[4] = 'e';
        buffer[5] = '\0';
    }
    
    return buffer;
}

bool Boolean::getValue() const {
    return value != 0;
}

Boolean Boolean::trueValue() {
    return Boolean(true);
}

Boolean Boolean::falseValue() {
    return Boolean(false);
}