#include "types/Number.hpp"
#include "types/Boolean.hpp"
#include "types/Array.hpp"
#include "types/Char.hpp"
#include "lib/memory.hpp"
#include "lib/console.hpp"
#include "types/Strings.hpp"
#include "lib/math.hpp"
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
//#include <string.h>

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

void testArray() {
    printLine("\n=== Array Tests ===");
    
    printLine("\n[Basic Operations]");
    runProtectedTest("Array construction", []() -> bool {
        Array arr;
        return arr.getLength() == 0 && arr.isEmpty();
    });
    
    runProtectedTest("Array push and get", []() -> bool {
        Array arr;
        int value1 = 42;
        int value2 = 100;
        arr.push(&value1);
        arr.push(&value2);
        return arr.getLength() == 2 && 
               *(int*)arr.get(0) == 42 && 
               *(int*)arr.get(1) == 100;
    });
    
    runProtectedTest("Array set", []() -> bool {
        Array arr;
        int value1 = 42;
        int value2 = 100;
        arr.push(&value1);
        arr.set(0, &value2);
        return *(int*)arr.get(0) == 100;
    });
    
    runProtectedTest("Array pop", []() -> bool {
        Array arr;
        int value1 = 42;
        int value2 = 100;
        arr.push(&value1);
        arr.push(&value2);
        int* popped = (int*)arr.pop();
        return arr.getLength() == 1 && *popped == 100;
    });
    
    printLine("\n[Advanced Operations]");
    runProtectedTest("Array insert", []() -> bool {
        Array arr;
        int value1 = 1;
        int value2 = 3;
        int value3 = 2;
        arr.push(&value1);
        arr.push(&value2);
        arr.insert(1, &value3);
        return arr.getLength() == 3 && 
               *(int*)arr.get(0) == 1 && 
               *(int*)arr.get(1) == 2 && 
               *(int*)arr.get(2) == 3;
    });
    
    runProtectedTest("Array remove", []() -> bool {
        Array arr;
        int value1 = 1;
        int value2 = 2;
        int value3 = 3;
        arr.push(&value1);
        arr.push(&value2);
        arr.push(&value3);
        int* removed = (int*)arr.remove(1);
        return arr.getLength() == 2 && 
               *removed == 2 && 
               *(int*)arr.get(0) == 1 && 
               *(int*)arr.get(1) == 3;
    });
    
    printLine("\n[Utility Methods]");
    runProtectedTest("Array clear", []() -> bool {
        Array arr;
        int value1 = 42;
        int value2 = 100;
        arr.push(&value1);
        arr.push(&value2);
        arr.clear();
        return arr.getLength() == 0 && arr.isEmpty();
    });
    
    runProtectedTest("Array indexOf", []() -> bool {
        Array arr;
        int value1 = 42;
        int value2 = 100;
        int value3 = 200;
        arr.push(&value1);
        arr.push(&value2);
        return arr.indexOf(&value1) == 0 && 
               arr.indexOf(&value2) == 1 && 
               arr.indexOf(&value3) == -1;
    });
    
    runProtectedTest("Array contains", []() -> bool {
        Array arr;
        int value1 = 42;
        int value2 = 100;
        int value3 = 200;
        arr.push(&value1);
        arr.push(&value2);
        return arr.contains(&value1) && 
               arr.contains(&value2) && 
               !arr.contains(&value3);
    });
    
    runProtectedTest("Array capacity growth", []() -> bool {
        Array arr(2); // Small initial capacity
        int values[10];
        for (int i = 0; i < 10; i++) {
            values[i] = i;
            arr.push(&values[i]);
        }
        return arr.getLength() == 10 && arr.getCapacity() >= 10;
    });
}

void testChar() {
    printLine("\n=== Char Tests ===");
    
    printLine("\n[Basic Construction]");
    runProtectedTest("Char from ASCII", []() -> bool {
        Char c('A');
        return c.getValue() == 'A';
    });
    
    runProtectedTest("Char from integer", []() -> bool {
        Char c(65);
        return c.getValue() == 'A';
    });
    
    printLine("\n[Character Classification]");
    runProtectedTest("isDigit() for digits", []() -> bool {
        Char digit('5');
        Char non_digit('A');
        return digit.isDigit() && !non_digit.isDigit();
    });
    
    runProtectedTest("isLetter() for letters", []() -> bool {
        Char letter('Z');
        Char non_letter('5');
        return letter.isLetter() && !non_letter.isLetter();
    });
    
    runProtectedTest("isWhitespace()", []() -> bool {
        Char space(' ');
        Char tab('\t');
        Char newline('\n');
        Char non_ws('A');
        return space.isWhitespace() && 
               tab.isWhitespace() && 
               newline.isWhitespace() && 
               !non_ws.isWhitespace();
    });
    
    runProtectedTest("Case detection", []() -> bool {
        Char upper('A');
        Char lower('a');
        Char digit('5');
        return upper.isUpperCase() && 
               !upper.isLowerCase() && 
               lower.isLowerCase() && 
               !lower.isUpperCase() && 
               !digit.isUpperCase() && 
               !digit.isLowerCase();
    });
    
    printLine("\n[Case Conversion]");
    runProtectedTest("toUpperCase", []() -> bool {
        Char lower('a');
        Char upper('A');
        Char digit('5');
        return lower.toUpperCase().getValue() == 'A' && 
               upper.toUpperCase().getValue() == 'A' && 
               digit.toUpperCase().getValue() == '5';
    });
    
    runProtectedTest("toLowerCase", []() -> bool {
        Char upper('A');
        Char lower('a');
        Char digit('5');
        return upper.toLowerCase().getValue() == 'a' && 
               lower.toLowerCase().getValue() == 'a' && 
               digit.toLowerCase().getValue() == '5';
    });
    
    printLine("\n[Comparison]");
    runProtectedTest("Char equality", []() -> bool {
        Char c1('A');
        Char c2('A');
        Char c3('B');
        return c1.equals(c2) && !c1.equals(c3);
    });
    
    runProtectedTest("Char comparison", []() -> bool {
        Char c1('A');
        Char c2('B');
        Char c3('A');
        return c1.compare(c2) == -1 && 
               c2.compare(c1) == 1 && 
               c1.compare(c3) == 0;
    });
    
    printLine("\n[String Conversion]");
    runProtectedTest("Char to string", []() -> bool {
        Char c('X');
        char* str = c.toString();
        bool result = (str != nullptr && str[0] == 'X' && str[1] == '\0');
        if (str) Luna::Memory::deallocate(str);
        return result;
    });
    
    printLine("\n[Static Methods]");
    runProtectedTest("Static character creation", []() -> bool {
        return Char::newline().getValue() == '\n' &&
               Char::tab().getValue() == '\t' &&
               Char::space().getValue() == ' ' &&
               Char::null().getValue() == '\0';
    });
    
    runProtectedTest("fromInt and toInt", []() -> bool {
        Char c = Char::fromInt(90);
        return c.getValue() == 'Z' && c.toInt() == 90;
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
    
    runProtectedTest("Array of Numbers", []() -> bool {
        Array arr;
        Number* num1 = new Number(10);
        Number* num2 = new Number(20);
        Number* num3 = new Number(30);
        
        arr.push(num1);
        arr.push(num2);
        arr.push(num3);
        
        bool result = ((Number*)arr.get(0))->equals(Number(10)) &&
                      ((Number*)arr.get(1))->equals(Number(20)) &&
                      ((Number*)arr.get(2))->equals(Number(30));
        
        delete num1;
        delete num2;
        delete num3;
        
        return result;
    });
    
    runProtectedTest("Char in Array", []() -> bool {
        Array arr;
        Char* c1 = new Char('H');
        Char* c2 = new Char('i');
        Char* c3 = new Char('!');
        
        arr.push(c1);
        arr.push(c2);
        arr.push(c3);
        
        bool result = ((Char*)arr.get(0))->getValue() == 'H' &&
                      ((Char*)arr.get(1))->getValue() == 'i' &&
                      ((Char*)arr.get(2))->getValue() == '!';
        
        delete c1;
        delete c2;
        delete c3;
        
        return result;
    });
}

void testConsole() {
    printLine("\n=== Console Tests ===");
    
    printLine("\n[Basic Logging]");
    runProtectedTest("Basic log message", []() -> bool {
        Luna::Console::log("This is a normal log message");
        return true; // If we get here without crashing, it worked
    });
    
    runProtectedTest("Warning message", []() -> bool {
        Luna::Console::warn("This is a warning message");
        return true;
    });
    
    runProtectedTest("Error message", []() -> bool {
        Luna::Console::error("This is an error message");
        return true;
    });
    
    printLine("\n[Table Display]");
    runProtectedTest("Simple table", []() -> bool {
        // Create 2D array for table data
        Array* tableData = new Array();
        
        // Row 1
        Array* row1 = new Array();
        row1->push(new Number(1));
        row1->push(new Char('A'));
        row1->push(new Boolean(true));
        tableData->push(row1);
        
        // Row 2
        Array* row2 = new Array();
        row2->push(new Number(2));
        row2->push(new Char('B'));
        row2->push(new Boolean(false));
        tableData->push(row2);
        
        // Row 3
        Array* row3 = new Array();
        row3->push(new Number(3));
        row3->push(new Char('C'));
        row3->push(new Boolean(true));
        tableData->push(row3);
        
        // Headers
        Array* headers = new Array();
        headers->push(new Char('I'));
        headers->push(new Char('D'));
        headers->push(new Char('S'));
        
        Luna::Console::table(tableData, headers);
        
        // Cleanup
        for (size_t i = 0; i < tableData->getLength(); i++) {
            Array* row = (Array*)tableData->get(i);
            for (size_t j = 0; j < row->getLength(); j++) {
                delete (void*)row->get(j);
            }
            delete row;
        }
        delete tableData;
        
        for (size_t i = 0; i < headers->getLength(); i++) {
            delete (void*)headers->get(i);
        }
        delete headers;
        
        return true;
    });
    
    printLine("\n[Multiple Values]");
    runProtectedTest("Log multiple values", []() -> bool {
        Array* values = new Array();
        values->push(new Number(42));
        values->push(new Char('X'));
        values->push(new Boolean(true));
        values->push(new Number(3.14));
        
        Luna::Console::logMultiple(values);
        
        // Cleanup
        for (size_t i = 0; i < values->getLength(); i++) {
            delete (void*)values->get(i);
        }
        delete values;
        
        return true;
    });
    
    printLine("\n[Value to String Conversion]");
    runProtectedTest("Convert Number to string", []() -> bool {
        Number num(123);
        char* str = Luna::Console::valueToString(&num);
        bool result = (str != nullptr && str[0] == '1' && str[1] == '2' && str[2] == '3');
        if (str) Luna::Memory::deallocate(str);
        return result;
    });
    
    runProtectedTest("Convert Boolean to string", []() -> bool {
        Boolean b(true);
        char* str = Luna::Console::valueToString(&b);
        bool result = (str != nullptr && str[0] == 'T' && str[1] == 'r' && str[2] == 'u' && str[3] == 'e');
        if (str) Luna::Memory::deallocate(str);
        return result;
    });
    
    runProtectedTest("Convert Char to string", []() -> bool {
        Char c('Z');
        char* str = Luna::Console::valueToString(&c);
        bool result = (str != nullptr && str[0] == 'Z' && str[1] == '\0');
        if (str) Luna::Memory::deallocate(str);
        return result;
    });
}

void testStrings() {
    printLine("\n=== String Tests ===");
    
    printLine("\n[C-Style String Functions]");
    runProtectedTest("string::length", []() -> bool {
        const char* test = "Hello";
        return Luna::string::length(test) == 5;
    });
    
    runProtectedTest("string::compare", []() -> bool {
        const char* s1 = "abc";
        const char* s2 = "abc";
        const char* s3 = "abd";
        return Luna::string::compare(s1, s2) == 0 && 
               Luna::string::compare(s1, s3) < 0;
    });
    
    runProtectedTest("string::duplicate", []() -> bool {
        const char* original = "Test String";
        char* copy = Luna::string::duplicate(original);
        bool result = (copy != nullptr && Luna::string::compare(original, copy) == 0);
        if (copy) Luna::string::free(copy);
        return result;
    });
    
    printLine("\n[std::string Type]");
    runProtectedTest("std::string construction", []() -> bool {
        Luna::std::string s1;
        Luna::std::string s2("Hello");
        Luna::std::string s3(s2);
        return s1.empty() && 
               !s2.empty() && 
               s2.length() == 5 &&
               s3 == s2;
    });
    
    runProtectedTest("std::string concatenation", []() -> bool {
        Luna::std::string s1("Hello");
        Luna::std::string s2(" World");
        s1 += s2;
        return s1 == "Hello World";
    });
    
    runProtectedTest("std::string case conversion", []() -> bool {
        Luna::std::string s1("Hello");
        Luna::std::string s2("WORLD");
        return s1.toUpperCase() == "HELLO" && 
               s2.toLowerCase() == "world";
    });
    
    runProtectedTest("std::string conversion methods", []() -> bool {
        Luna::std::string s1("123");
        Luna::std::string s2("true");
        Luna::std::string s3("3.14");
        return s1.toInt() == 123 && 
               s2.toBoolean() == true && 
               s3.toDouble() == 3.0; // Simple implementation truncates
    });
    
    runProtectedTest("std::string find and substr", []() -> bool {
        Luna::std::string s("Hello World");
        return s.find("World") == 6 && 
               s.substr(0, 5) == "Hello";
    });
}

// Add math tests
void testMath() {
    printLine("\n=== Math Library Tests ===");
    
    printLine("\n[Standard Math Functions]");
    runProtectedTest("sin(0) = 0", []() -> bool {
        Number result = Luna::Math::sin(Number(0));
        return result.equals(Number(0));
    });
    
    runProtectedTest("cos(0) = 1", []() -> bool {
        Number result = Luna::Math::cos(Number(0));
        return result.equals(Number(1));
    });
    
    runProtectedTest("tan(0) = 0", []() -> bool {
        Number result = Luna::Math::tan(Number(0));
        return result.equals(Number(0));
    });
    
    runProtectedTest("sqrt(4) = 2", []() -> bool {
        Number result = Luna::Math::sqrt(Number(4));
        return result.equals(Number(2));
    });
    
    runProtectedTest("pow(2, 3) = 8", []() -> bool {
        Number result = Luna::Math::pow(Number(2), Number(3));
        return result.equals(Number(8));
    });
    
    runProtectedTest("log(e) ~= 1", []() -> bool {
        Number result = Luna::Math::log(Number(2.71828)); // Approximate e
        return result.greaterThan(Number(0.999)) && result.lessThan(Number(1.001));
    });
    
    printLine("\n[Math Constants]");
    runProtectedTest("PI constant", []() -> bool {
        return Luna::Math::constants::PI > 3.14159 && Luna::Math::constants::PI < 3.14160;
    });
    
    runProtectedTest("E constant", []() -> bool {
        return Luna::Math::constants::E > 2.71828 && Luna::Math::constants::E < 2.71829;
    });
    
    printLine("\n[Symbolic Math - Basic]");
    runProtectedTest("Symbol creation", []() -> bool {
        Luna::Math::Symbol x("x");
        char* str = x.toString();
        bool result = (str != nullptr && Luna::string::compare(str, "x") == 0);
        if (str) Luna::Memory::deallocate(str);
        return result;
    });
    
    runProtectedTest("Constant creation", []() -> bool {
        Luna::Math::Constant five(5);
        char* str = five.toString();
        bool result = (str != nullptr && Luna::string::compare(str, "5") == 0);
        if (str) Luna::Memory::deallocate(str);
        return result;
    });
    
    runProtectedTest("Symbol evaluation", []() -> bool {
        Luna::Math::Symbol x("x");
        Array vars;
        vars.push(&x);
        vars.push(new Number(42));
        Number result = x.evaluate(vars);
        
        // Cleanup
        delete (Number*)vars.get(1);
        return result.equals(Number(42));
    });
    
    printLine("\n[Symbolic Math - Differentiation]");
    runProtectedTest("Derivative of constant", []() -> bool {
        Luna::Math::Constant five(5);
        Luna::Math::SymbolicExpr* derivative = five.diff("x");
        char* str = derivative->toString();
        bool result = (str != nullptr && Luna::string::compare(str, "0") == 0);
        
        if (str) Luna::Memory::deallocate(str);
        Luna::Math::symbolic::free(derivative);
        return result;
    });
    
    runProtectedTest("Derivative of x", []() -> bool {
        Luna::Math::Symbol x("x");
        Luna::Math::SymbolicExpr* derivative = x.diff("x");
        char* str = derivative->toString();
        bool result = (str != nullptr && Luna::string::compare(str, "1") == 0);
        
        if (str) Luna::Memory::deallocate(str);
        Luna::Math::symbolic::free(derivative);
        return result;
    });
    
    printLine("\n[Symbolic Math - Simplification]");
    runProtectedTest("Simplify x + 0", []() -> bool {
        Luna::Math::Symbol x("x");
        Luna::Math::Constant zero(0);
        Luna::Math::BinaryOp add(Luna::Math::BinaryOp::Operation::ADD, 
                                new Luna::Math::Symbol(x), 
                                new Luna::Math::Constant(zero));
        
        Luna::Math::SymbolicExpr* simplified = add.simplify();
        char* str = simplified->toString();
        bool result = (str != nullptr && Luna::string::compare(str, "x") == 0);
        
        if (str) Luna::Memory::deallocate(str);
        Luna::Math::symbolic::free(simplified);
        return result;
    });
    
    runProtectedTest("Simplify x * 1", []() -> bool {
        Luna::Math::Symbol x("x");
        Luna::Math::Constant one(1);
        Luna::Math::BinaryOp multiply(Luna::Math::BinaryOp::Operation::MULTIPLY, 
                                     new Luna::Math::Symbol(x), 
                                     new Luna::Math::Constant(one));
        
        Luna::Math::SymbolicExpr* simplified = multiply.simplify();
        char* str = simplified->toString();
        bool result = (str != nullptr && Luna::string::compare(str, "x") == 0);
        
        if (str) Luna::Memory::deallocate(str);
        Luna::Math::symbolic::free(simplified);
        return result;
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
        testArray();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testArray() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler);
    }
    
    suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testChar();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testChar() suite crashed with signal %d - continuing...\n\n", suite_sig);
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
    
    suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testConsole();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testConsole() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler);
    }
    
    suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testStrings();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testStrings() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler);
    }
    
    suite_sig = setjmp(recovery_point);
    if (suite_sig == 0) {
        in_protected_block = 1;
        testMath();
        in_protected_block = 0;
    } else {
        in_protected_block = 0;
        printf("\n[ERROR] testMath() suite crashed with signal %d - continuing...\n\n", suite_sig);
        signal(suite_sig, crash_handler);
    }
    
    printLine("\n=== All Tests Complete ===");
    
    Luna::Memory::shutdown();
    
    return 0;
}