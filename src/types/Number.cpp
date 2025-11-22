#include "Number.hpp"
#include "lib/memory.hpp"

extern "C" void* luna_malloc(unsigned long size);
extern "C" void luna_free(void* ptr);
extern "C" void luna_memcpy(void* dest, void* src, unsigned long n);

Number::Number(int32_t value) : type_tag(0), int_val(value) {}
Number::Number(double value) : type_tag(1), float_val(value) {}

Number Number::add(const Number& other) const {
    if (type_tag == 0 && other.type_tag == 0) {
        int32_t result;
        __asm__ volatile (
            "addl %2, %0"
            : "=r" (result)
            : "0" (int_val), "r" (other.int_val)
        );
        return Number(result);
    }
    double a = toDouble();
    double b = other.toDouble();
    double result;
    __asm__ volatile (
        "addsd %2, %0"
        : "=x" (result)
        : "0" (a), "x" (b)
    );
    return Number(result);
}

Number Number::subtract(const Number& other) const {
    if (type_tag == 0 && other.type_tag == 0) {
        int32_t result;
        __asm__ volatile (
            "subl %2, %0"
            : "=r" (result)
            : "0" (int_val), "r" (other.int_val)
        );
        return Number(result);
    }
    double a = toDouble();
    double b = other.toDouble();
    double result;
    __asm__ volatile (
        "subsd %2, %0"
        : "=x" (result)
        : "0" (a), "x" (b)
    );
    return Number(result);
}

Number Number::multiply(const Number& other) const {
    if (type_tag == 0 && other.type_tag == 0) {
        int32_t result;
        __asm__ volatile (
            "imull %2, %0"
            : "=r" (result)
            : "0" (int_val), "r" (other.int_val)
        );
        return Number(result);
    }
    double a = toDouble();
    double b = other.toDouble();
    double result;
    __asm__ volatile (
        "mulsd %2, %0"
        : "=x" (result)
        : "0" (a), "x" (b)
    );
    return Number(result);
}

Number Number::divide(const Number& other) const {
    double a = toDouble();
    double b = other.toDouble();
    
    double result;
    __asm__ volatile (
        "divsd %2, %0"
        : "=x" (result)
        : "0" (a), "x" (b)
    );
    return Number(result);
}

bool Number::equals(const Number& other) const {
    if (isNaN() || other.isNaN()) return false;
    double a = toDouble();
    double b = other.toDouble();
    int result;
    __asm__ volatile (
        "ucomisd %2, %1\n"
        "sete %b0\n"
        "movzbl %b0, %0\n"
        : "=r" (result)
        : "x" (a), "x" (b)
    );
    return result;
}

bool Number::lessThan(const Number& other) const {
    if (isNaN() || other.isNaN()) return false;
    double a = toDouble();
    double b = other.toDouble();
    int result;
    __asm__ volatile (
        "ucomisd %2, %1\n"
        "setb %b0\n"
        "movzbl %b0, %0\n"
        : "=r" (result)
        : "x" (a), "x" (b)
    );
    return result;
}

bool Number::greaterThan(const Number& other) const {
    if (isNaN() || other.isNaN()) return false;
    double a = toDouble();
    double b = other.toDouble();
    int result;
    __asm__ volatile (
        "ucomisd %2, %1\n"
        "seta %b0\n"
        "movzbl %b0, %0\n"
        : "=r" (result)
        : "x" (a), "x" (b)
    );
    return result;
}

bool Number::toBoolean() const {
    if (isNaN()) return false;
    double val = toDouble();
    double zero = 0.0;
    int result;
    __asm__ volatile (
        "ucomisd %2, %1\n"
        "setne %b0\n"
        "movzbl %b0, %0\n"
        : "=r" (result)
        : "x" (val), "x" (zero)
    );
    return result;
}

char* Number::toString() const {
    char* buffer = (char*)luna_malloc(32);
    if (isNaN()) {
        buffer[0] = 'N';
        buffer[1] = 'a';
        buffer[2] = 'N';
        buffer[3] = '\0';
    } else if (isInfinity()) {
        if (float_val > 0) {
            buffer[0] = 'I';
            buffer[1] = 'n';
            buffer[2] = 'f';
            buffer[3] = 'i';
            buffer[4] = 'n';
            buffer[5] = 'i';
            buffer[6] = 't';
            buffer[7] = 'y';
            buffer[8] = '\0';
        } else {
            buffer[0] = '-';
            buffer[1] = 'I';
            buffer[2] = 'n';
            buffer[3] = 'f';
            buffer[4] = 'i';
            buffer[5] = 'n';
            buffer[6] = 'i';
            buffer[7] = 't';
            buffer[8] = 'y';
            buffer[9] = '\0';
        }
    } else if (type_tag == 0) {
        intToString(int_val, buffer);
    } else {
        doubleToString(float_val, buffer);
    }
    return buffer;
}

Number Number::nan() {
    double nan_val = 0.0 / 0.0;
    return Number(nan_val);
}

Number Number::infinity() {
    double inf_val = 1.0 / 0.0;
    return Number(inf_val);
}

Number Number::negativeInfinity() {
    double neg_inf = -1.0 / 0.0;
    return Number(neg_inf);
}

bool Number::isInt() const {
    return type_tag == 0;
}

bool Number::isFloat() const {
    return type_tag == 1;
}

bool Number::isNaN() const {
    if (type_tag != 1) return false;
    return float_val != float_val;
}

bool Number::isInfinity() const {
    if (type_tag != 1) return false;
    double inf_val = 1.0 / 0.0;
    return (float_val == inf_val) || (float_val == -inf_val);
}

double Number::toDouble() const {
    if (type_tag == 0) {
        return (double)int_val;
    }
    return float_val;
}

void Number::intToString(int32_t value, char* buffer) const {
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    char temp[32];
    int i = 0;
    int is_negative = 0;
    
    if (value < 0) {
        is_negative = 1;
        value = -value;
    }
    
    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }
    
    int j = 0;
    if (is_negative) {
        buffer[j++] = '-';
    }
    
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
}

void Number::doubleToString(double value, char* buffer) const {
    int32_t int_part = (int32_t)value;
    intToString(int_part, buffer);
}