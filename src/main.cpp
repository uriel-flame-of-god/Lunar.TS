#include "types/Number.hpp"
#include "types/Boolean.hpp"
#include "lib/memory.hpp"
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>

// Global jump buffer for crash recovery
static jmp_buf recovery_point;
static volatile sig_atomic_t in_protected_block = 0;

/**
 * @brief Signal handler for crashes
 */
void crash_handler(int sig) {
    // Re-register the handler for next time
    signal(sig, crash_handler);
    
    if (in_protected_block) {
        in_protected_block = 0;
        longjmp(recovery_point, sig);
    } else {
        // If not in protected block, just exit
        printf("\n[FATAL] Unhandled signal %d outside protected block\n", sig);
        _exit(1);
    }
}

/**
 * @brief Print test result
 */
void printTest(const char* name, bool passed) {
    printf("[%s] %s\n", passed ? "PASS" : "FAIL", name);
}

void printLine(const char* str) {
    printf("%s\n", str);
}

/**
 * @brief Run a test with crash protection
 */
template<typename TestFunc>
void runProtectedTest(const char* name, TestFunc test) {
    int sig = setjmp(recovery_point);
    if (sig == 0) {
        in_protected_block = 1;
        bool result = test();
        in_protected_block = 0;
        printTest(name, result);
    } else {
        in_protected_block = 0;
        printf("[CRASH] Signal %d caught in test: %s\n", sig, name);
        printTest(name, false);
    }
}

void testNumber() {
    printLine("\n=== Number Tests ===");
    
    printLine("\n[Integer Arithmetic]");
    runProtectedTest("Addition: 10 + 3 = 13", []() -> bool {
        Number a(10);
        Number b(3);
        Number sum = a.add(b);
        return sum.equals(Number(13));
    });
    
    runProtectedTest("Subtraction: 10 - 3 = 7", []() -> bool {
        Number a(10);
        Number b(3);
        Number diff = a.subtract(b);
        return diff.equals(Number(7));
    });
    
    runProtectedTest("Multiplication: 10 * 3 = 30", []() -> bool {
        Number a(10);
        Number b(3);
        Number prod = a.multiply(b);
        return prod.equals(Number(30));
    });
    
    runProtectedTest("Division returns float", []() -> bool {
        Number a(10);
        Number b(3);
        Number quot = a.divide(b);
        return quot.isFloat();
    });
    
    printLine("\n[Float Arithmetic]");
    runProtectedTest("Float addition", []() -> bool {
        Number fa(5.5);
        Number fb(2.2);
        Number fsum = fa.add(fb);
        return fsum.isFloat();
    });
    
    runProtectedTest("Float subtraction", []() -> bool {
        Number fa(5.5);
        Number fb(2.2);
        Number fsub = fa.subtract(fb);
        return fsub.isFloat();
    });
    
    runProtectedTest("Float multiplication", []() -> bool {
        Number fa(5.5);
        Number fb(2.2);
        Number fmul = fa.multiply(fb);
        return fmul.isFloat();
    });
    
    runProtectedTest("Float division", []() -> bool {
        Number fa(5.5);
        Number fb(2.2);
        Number fdiv = fa.divide(fb);
        return fdiv.isFloat();
    });
    
    printLine("\n[Comparisons]");
    runProtectedTest("Equality: 42 == 42", []() -> bool {
        Number x(42);
        Number y(42);
        return x.equals(y);
    });
    
    runProtectedTest("Inequality: 42 != 50", []() -> bool {
        Number x(42);
        Number z(50);
        return !x.equals(z);
    });
    
    runProtectedTest("Less than: 42 < 50", []() -> bool {
        Number x(42);
        Number z(50);
        return x.lessThan(z);
    });
    
    runProtectedTest("Greater than: 50 > 42", []() -> bool {
        Number x(42);
        Number z(50);
        return z.greaterThan(x);
    });
    
    printLine("\n[Type Conversion]");
    runProtectedTest("isInt() for int", []() -> bool {
        Number int_num(99);
        return int_num.isInt();
    });
    
    runProtectedTest("isFloat() for float", []() -> bool {
        Number float_num(99.99);
        return float_num.isFloat();
    });
    
    runProtectedTest("toBoolean() non-zero", []() -> bool {
        Number int_num(99);
        return int_num.toBoolean();
    });
    
    runProtectedTest("toBoolean() zero", []() -> bool {
        Number zero(0);
        return !zero.toBoolean();
    });
    
    printLine("\n[Special Values]");
    runProtectedTest("NaN detection", []() -> bool {
        Number nan_val = Number::nan();
        return nan_val.isNaN();
    });
    
    runProtectedTest("NaN != NaN", []() -> bool {
        Number nan_val = Number::nan();
        return !nan_val.equals(nan_val);
    });
    
    runProtectedTest("Infinity detection", []() -> bool {
        Number inf = Number::infinity();
        return inf.isInfinity();
    });
    
    runProtectedTest("Negative infinity detection", []() -> bool {
        Number neg_inf = Number::negativeInfinity();
        return neg_inf.isInfinity();
    });
    
    printLine("\n[Division by Zero]");
    runProtectedTest("1 / 0 = Infinity", []() -> bool {
        Number dividend(1);
        Number zero_divisor(0);
        Number div_result = dividend.divide(zero_divisor);
        return div_result.isInfinity();
    });
    
    runProtectedTest("0 / 0 = NaN", []() -> bool {
        Number zero_dividend(0);
        Number zero_divisor(0);
        Number zero_zero = zero_dividend.divide(zero_divisor);
        return zero_zero.isNaN();
    });
    
    printLine("\n[String Conversion]");
    runProtectedTest("Integer to string: 123", []() -> bool {
        Number n1(123);
        char* s1 = n1.toString();
        bool result = (s1 != nullptr && s1[0] == '1' && s1[1] == '2' && s1[2] == '3');
        if (s1) Luna::Memory::deallocate(s1);
        return result;
    });
    
    runProtectedTest("Negative to string: -456", []() -> bool {
        Number n2(-456);
        char* s2 = n2.toString();
        bool result = (s2 != nullptr && s2[0] == '-' && s2[1] == '4');
        if (s2) Luna::Memory::deallocate(s2);
        return result;
    });
    
    runProtectedTest("NaN to string", []() -> bool {
        Number n3 = Number::nan();
        char* s3 = n3.toString();
        bool result = (s3 != nullptr && s3[0] == 'N' && s3[1] == 'a' && s3[2] == 'N');
        if (s3) Luna::Memory::deallocate(s3);
        return result;
    });
    
    runProtectedTest("Infinity to string", []() -> bool {
        Number n4 = Number::infinity();
        char* s4 = n4.toString();
        bool result = (s4 != nullptr && s4[0] == 'I' && s4[1] == 'n' && s4[2] == 'f');
        if (s4) Luna::Memory::deallocate(s4);
        return result;
    });
}

void testBoolean() {
    printLine("\n=== Boolean Tests ===");
    
    printLine("\n[Basic Construction]");
    runProtectedTest("Boolean(true) returns true", []() -> bool {
        Boolean b_true(true);
        return b_true.getValue();
    });
    
    runProtectedTest("Boolean(false) returns false", []() -> bool {
        Boolean b_false(false);
        return !b_false.getValue();
    });
    
    printLine("\n[Logical Operations]");
    runProtectedTest("true AND true = true", []() -> bool {
        Boolean b_true(true);
        Boolean t1 = b_true.logicalAnd(b_true);
        return t1.getValue();
    });
    
    runProtectedTest("true AND false = false", []() -> bool {
        Boolean b_true(true);
        Boolean b_false(false);
        Boolean t2 = b_true.logicalAnd(b_false);
        return !t2.getValue();
    });
    
    runProtectedTest("false AND false = false", []() -> bool {
        Boolean b_false(false);
        Boolean t3 = b_false.logicalAnd(b_false);
        return !t3.getValue();
    });
    
    runProtectedTest("true OR true = true", []() -> bool {
        Boolean b_true(true);
        Boolean t4 = b_true.logicalOr(b_true);
        return t4.getValue();
    });
    
    runProtectedTest("true OR false = true", []() -> bool {
        Boolean b_true(true);
        Boolean b_false(false);
        Boolean t5 = b_true.logicalOr(b_false);
        return t5.getValue();
    });
    
    runProtectedTest("false OR false = false", []() -> bool {
        Boolean b_false(false);
        Boolean t6 = b_false.logicalOr(b_false);
        return !t6.getValue();
    });
    
    printLine("\n[Logical NOT]");
    runProtectedTest("NOT true = false", []() -> bool {
        Boolean b_true(true);
        Boolean t7 = b_true.logicalNot();
        return !t7.getValue();
    });
    
    runProtectedTest("NOT false = true", []() -> bool {
        Boolean b_false(false);
        Boolean t8 = b_false.logicalNot();
        return t8.getValue();
    });
    
    printLine("\n[Equality]");
    runProtectedTest("true == true", []() -> bool {
        Boolean b_true(true);
        return b_true.equals(b_true);
    });
    
    runProtectedTest("false == false", []() -> bool {
        Boolean b_false(false);
        return b_false.equals(b_false);
    });
    
    runProtectedTest("true != false", []() -> bool {
        Boolean b_true(true);
        Boolean b_false(false);
        return !b_true.equals(b_false);
    });
    
    runProtectedTest("false != true", []() -> bool {
        Boolean b_true(true);
        Boolean b_false(false);
        return !b_false.equals(b_true);
    });
    
    printLine("\n[String Conversion]");
    runProtectedTest("Boolean(true) to string = 'True'", []() -> bool {
        Boolean b_true(true);
        char* s_true = b_true.toString();
        bool result = (s_true != nullptr && s_true[0] == 'T' && s_true[1] == 'r' && s_true[2] == 'u' && s_true[3] == 'e');
        if (s_true) Luna::Memory::deallocate(s_true);
        return result;
    });
    
    runProtectedTest("Boolean(false) to string = 'False'", []() -> bool {
        Boolean b_false(false);
        char* s_false = b_false.toString();
        bool result = (s_false != nullptr && s_false[0] == 'F' && s_false[1] == 'a' && s_false[2] == 'l' && s_false[3] == 's' && s_false[4] == 'e');
        if (s_false) Luna::Memory::deallocate(s_false);
        return result;
    });
    
    printLine("\n[Static Factory Methods]");
    runProtectedTest("Boolean::trueValue() returns true", []() -> bool {
        Boolean static_true = Boolean::trueValue();
        return static_true.getValue();
    });
    
    runProtectedTest("Boolean::falseValue() returns false", []() -> bool {
        Boolean static_false = Boolean::falseValue();
        return !static_false.getValue();
    });
    
    runProtectedTest("trueValue() equals Boolean(true)", []() -> bool {
        Boolean static_true = Boolean::trueValue();
        Boolean b_true(true);
        return static_true.equals(b_true);
    });
    
    runProtectedTest("falseValue() equals Boolean(false)", []() -> bool {
        Boolean static_false = Boolean::falseValue();
        Boolean b_false(false);
        return static_false.equals(b_false);
    });
}

void testMemory() {
    printLine("\n=== Memory Management Tests ===");
    
    runProtectedTest("Memory allocation success", []() -> bool {
        void* mem1 = Luna::Memory::allocate(256);
        bool result = (mem1 != nullptr);
        if (mem1) Luna::Memory::deallocate(mem1);
        return result;
    });
    
    runProtectedTest("Memory set/fill", []() -> bool {
        void* mem1 = Luna::Memory::allocate(256);
        if (!mem1) return false;
        Luna::Memory::set(mem1, 0x42, 10);
        char* cmem = (char*)mem1;
        bool result = (cmem[0] == 0x42 && cmem[9] == 0x42);
        Luna::Memory::deallocate(mem1);
        return result;
    });
    
    runProtectedTest("Memory copy", []() -> bool {
        void* mem1 = Luna::Memory::allocate(256);
        void* mem2 = Luna::Memory::allocate(128);
        if (!mem1 || !mem2) {
            if (mem1) Luna::Memory::deallocate(mem1);
            if (mem2) Luna::Memory::deallocate(mem2);
            return false;
        }
        Luna::Memory::set(mem1, 0x42, 10);
        Luna::Memory::copy(mem2, mem1, 10);
        char* cmem2 = (char*)mem2;
        bool result = (cmem2[0] == 0x42 && cmem2[9] == 0x42);
        Luna::Memory::deallocate(mem1);
        Luna::Memory::deallocate(mem2);
        return result;
    });
    
    runProtectedTest("Memory compare (equal)", []() -> bool {
        void* mem1 = Luna::Memory::allocate(256);
        void* mem2 = Luna::Memory::allocate(128);
        if (!mem1 || !mem2) {
            if (mem1) Luna::Memory::deallocate(mem1);
            if (mem2) Luna::Memory::deallocate(mem2);
            return false;
        }
        Luna::Memory::set(mem1, 0x42, 10);
        Luna::Memory::copy(mem2, mem1, 10);
        int cmp_result = Luna::Memory::compare(mem1, mem2, 10);
        bool result = (cmp_result == 0);
        Luna::Memory::deallocate(mem1);
        Luna::Memory::deallocate(mem2);
        return result;
    });
    
    runProtectedTest("Memory deallocation", []() -> bool {
        void* mem = Luna::Memory::allocate(256);
        if (mem) Luna::Memory::deallocate(mem);
        return true;
    });
}

void testIntegration() {
    printLine("\n=== Integration Tests ===");
    
    runProtectedTest("Number(42).toBoolean() = true", []() -> bool {
        Number positive_num(42);
        return positive_num.toBoolean();
    });
    
    runProtectedTest("Number(0).toBoolean() = false", []() -> bool {
        Number zero_num(0);
        return !zero_num.toBoolean();
    });
    
    runProtectedTest("Number(-5).toBoolean() = true", []() -> bool {
        Number negative_num(-5);
        return negative_num.toBoolean();
    });
    
    runProtectedTest("10 < 20 creates Boolean(true)", []() -> bool {
        Number num1(10);
        Number num2(20);
        Boolean comp_result(num1.lessThan(num2));
        return comp_result.getValue();
    });
    
    runProtectedTest("true AND false integration", []() -> bool {
        Boolean b1(true);
        Boolean b2(false);
        Boolean and_result = b1.logicalAnd(b2);
        return !and_result.getValue();
    });
}

int main() {
    // Set up signal handlers that will re-register themselves
    signal(SIGSEGV, crash_handler);
    signal(SIGFPE, crash_handler);
    signal(SIGILL, crash_handler);
    signal(SIGABRT, crash_handler);
    signal(SIGBUS, crash_handler);
    
    Luna::Memory::initialize();
    
    printLine("=== Luna Type System Tests ===");
    printLine("(Tests will continue even if some crash)\n");
    
    // Run all test suites - each function call is also protected
    int suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testNumber();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testNumber() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler); // Re-register
    }
    
    suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testBoolean();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testBoolean() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler);
    }
    
    suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testMemory();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testMemory() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler);
    }
    
    suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testIntegration();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testIntegration() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler);
    }
    
    printLine("\n=== All Tests Complete ===");
    
    Luna::Memory::shutdown();
    
    return 0;
}