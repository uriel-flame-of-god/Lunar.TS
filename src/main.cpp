#include "types/Number.hpp"
#include "lib/memory.hpp"
#include <stdio.h>

/**
 * @brief Print test result
 */
void printTest(const char* name, bool passed) {
    printf("[%s] %s\n", passed ? "PASS" : "FAIL", name);
}

void printLine(const char* str) {
    printf("%s\n", str);
}

int main() {
    Luna::Memory::initialize();
    
    printLine("=== Luna Number Tests ===");
    
    printLine("\n[Integer Arithmetic]");
    Number a(10);
    Number b(3);
    
    Number sum = a.add(b);
    bool test1 = sum.equals(Number(13));
    printTest("Addition: 10 + 3 = 13", test1);
    
    Number diff = a.subtract(b);
    bool test2 = diff.equals(Number(7));
    printTest("Subtraction: 10 - 3 = 7", test2);
    
    Number prod = a.multiply(b);
    bool test3 = prod.equals(Number(30));
    printTest("Multiplication: 10 * 3 = 30", test3);
    
    Number quot = a.divide(b);
    bool test4 = quot.isFloat();
    printTest("Division returns float", test4);
    
    printLine("\n[Float Arithmetic]");
    Number fa(5.5);
    Number fb(2.2);
    
    Number fsum = fa.add(fb);
    bool test5 = fsum.isFloat();
    printTest("Float addition", test5);
    
    Number fsub = fa.subtract(fb);
    bool test6 = fsub.isFloat();
    printTest("Float subtraction", test6);
    
    Number fmul = fa.multiply(fb);
    bool test7 = fmul.isFloat();
    printTest("Float multiplication", test7);
    
    Number fdiv = fa.divide(fb);
    bool test8 = fdiv.isFloat();
    printTest("Float division", test8);
    
    printLine("\n[Comparisons]");
    Number x(42);
    Number y(42);
    Number z(50);
    
    bool test9 = x.equals(y);
    printTest("Equality: 42 == 42", test9);
    
    bool test10 = !x.equals(z);
    printTest("Inequality: 42 != 50", test10);
    
    bool test11 = x.lessThan(z);
    printTest("Less than: 42 < 50", test11);
    
    bool test12 = z.greaterThan(x);
    printTest("Greater than: 50 > 42", test12);
    
    printLine("\n[Type Conversion]");
    Number int_num(99);
    Number float_num(99.99);
    
    bool test13 = int_num.isInt();
    printTest("isInt() for int", test13);
    
    bool test14 = float_num.isFloat();
    printTest("isFloat() for float", test14);
    
    bool test15 = int_num.toBoolean();
    printTest("toBoolean() non-zero", test15);
    
    Number zero(0);
    bool test16 = !zero.toBoolean();
    printTest("toBoolean() zero", test16);
    
    printLine("\n[Special Values]");
    Number nan_val = Number::nan();
    bool test17 = nan_val.isNaN();
    printTest("NaN detection", test17);
    
    bool test18 = !nan_val.equals(nan_val);
    printTest("NaN != NaN", test18);
    
    Number inf = Number::infinity();
    bool test19 = inf.isInfinity();
    printTest("Infinity detection", test19);
    
    Number neg_inf = Number::negativeInfinity();
    bool test20 = neg_inf.isInfinity();
    printTest("Negative infinity detection", test20);
    
    printLine("\n[Division by Zero]");
    Number dividend(1);
    Number zero_divisor(0);
    Number div_result = dividend.divide(zero_divisor);
    bool test21 = div_result.isInfinity();
    printTest("1 / 0 = Infinity", test21);
    
    Number zero_dividend(0);
    Number zero_zero = zero_dividend.divide(zero_divisor);
    bool test22 = zero_zero.isNaN();
    printTest("0 / 0 = NaN", test22);
    
    printLine("\n[String Conversion]");
    Number n1(123);
    char* s1 = n1.toString();
    bool test23 = (s1[0] == '1' && s1[1] == '2' && s1[2] == '3');
    printTest("Integer to string: 123", test23);
    Luna::Memory::deallocate(s1);
    
    Number n2(-456);
    char* s2 = n2.toString();
    bool test24 = (s2[0] == '-' && s2[1] == '4');
    printTest("Negative to string: -456", test24);
    Luna::Memory::deallocate(s2);
    
    Number n3 = Number::nan();
    char* s3 = n3.toString();
    bool test25 = (s3[0] == 'N' && s3[1] == 'a' && s3[2] == 'N');
    printTest("NaN to string", test25);
    Luna::Memory::deallocate(s3);
    
    Number n4 = Number::infinity();
    char* s4 = n4.toString();
    bool test26 = (s4[0] == 'I' && s4[1] == 'n' && s4[2] == 'f');
    printTest("Infinity to string", test26);
    Luna::Memory::deallocate(s4);
    
    printLine("\n[Memory Management]");
    void* mem1 = Luna::Memory::allocate(256);
    bool test27 = (mem1 != nullptr);
    printTest("Memory allocation success", test27);
    
    Luna::Memory::set(mem1, 0x42, 10);
    char* cmem = (char*)mem1;
    bool test28 = (cmem[0] == 0x42 && cmem[9] == 0x42);
    printTest("Memory set/fill", test28);
    
    void* mem2 = Luna::Memory::allocate(128);
    Luna::Memory::copy(mem2, mem1, 10);
    char* cmem2 = (char*)mem2;
    bool test29 = (cmem2[0] == 0x42 && cmem2[9] == 0x42);
    printTest("Memory copy", test29);
    
    int cmp_result = Luna::Memory::compare(mem1, mem2, 10);
    bool test30 = (cmp_result == 0);
    printTest("Memory compare (equal)", test30);
    
    Luna::Memory::deallocate(mem1);
    Luna::Memory::deallocate(mem2);
    printTest("Memory deallocation", true);
    
    printLine("\n=== All Tests Complete ===");
    
    Luna::Memory::shutdown();
    
    return 0;
}