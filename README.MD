# 🌙 Lunar.TS

> **A Mad Science Experiment in TypeScript Runtimes**  
> *Building a TypeScript runtime from scratch, one assembly instruction at a time*

[![Status](https://img.shields.io/badge/status-97.32%25%20complete-brightgreen)](https://github.com/uriel-flame-of-god/Lunar.TS)
[![Tests](https://img.shields.io/badge/tests-109%2F112%20passing-success)](https://github.com/uriel-flame-of-god/Lunar.TS)
[![Fails](https://img.shields.io/badge/failures-3%20remaining-red)](https://github.com/uriel-flame-of-god/Lunar.TS)
[![Assembly](https://img.shields.io/badge/contains-asm%20magic-blue)](https://github.com/uriel-flame-of-god/Lunar.TS)
[![Madness](https://img.shields.io/badge/madness-level%3A%20lunar-purple)](https://github.com/uriel-flame-of-god/Lunar.TS)

## 🎯 What is This Madness?

Lunar.TS is my **personal playground** for building a TypeScript runtime from absolute scratch. 

**Why?** Because:
- I thought it would be fun 💀
- I wanted to see if I could 🗣  
- I enjoy pain and assembly programming 🙏
- Maybe someday I'll run TypeScript on bare metal (probably not, but let's pretend)

## 📊 Current Achievement: **112 Tests, 97.32% Success!** 🚀

HOLY MOLY! The madness has reached new heights! I now have:

### ✅ What Actually Works (109/112 PASSING!)

- **Number class** - 24/24 tests passing! 🧮
- **Boolean class** - 20/20 tests passing! ⚡  
- **Array class** - 11/11 tests passing! 🧩
- **Char class** - 14/14 tests passing! 🔤
- **String types** - 8/8 tests passing! 📋
- **Memory management** - 5/5 tests passing! 🗳️
- **Integration tests** - 7/7 tests passing! 🔗
- **Math Library** - 17/18 tests passing! 🧮
- **Console system** - 3/5 tests passing! 🎨

### 🚨 The Three Stubborn Failures

1. **Console Number to string** - Type detection edge case
2. **Console Char to string** - Type detection edge case  
3. **Math log(e) precision** - Floating point accuracy

## 🏗 "Architecture" (I'm Using That Term Loosely)

```
TypeScript Dreams ───────┐
                        ↓
   Number.cpp ──24/24─> PERFECT MATH!
   Boolean.cpp ─20/20─> PERFECT LOGIC!
   Array.cpp ──11/11─> PERFECT ARRAYS!
   Char.cpp ───14/14─> PERFECT CHARACTERS!
   Strings.cpp ─8/8──> PERFECT STRINGS!
   Memory.cpp ─5/5──> PERFECT MEMORY!
   Math.cpp ──17/18─> NEAR PERFECT MATH!
   Console.cpp ─3/5──> ALMOST PERFECT OUTPUT!
                        ↑
   Assembly Madness ────┘
```

### The Grand Vision (Delusions)

1. ~~Build a Number type~~ ✅ **PERFECT! (24/24)**
2. ~~Build a Boolean type~~ ✅ **PERFECT! (20/20)**
3. ~~Build an Array type~~ ✅ **PERFECT! (11/11)**
4. ~~Build a Char type~~ ✅ **PERFECT! (14/14)**
5. ~~Build String types~~ ✅ **PERFECT! (8/8)**
6. ~~Build Memory system~~ ✅ **PERFECT! (5/5)**
7. ~~Build Math Library~~ ✅ **NEAR PERFECT! (17/18)**
8. **Fix those last 3 tests!** 🎯
9. **ACHIEVE 112/112 PERFECT SCORE!** 🏆
10. Profit! (just kidding, there's no profit)

## 🛠 How to Run This Masterpiece

```bash
# Clone this monument to poor life choices
git clone https://github.com/uriel-flame-of-god/Lunar.TS
cd Lunar.TS

# Run the thing
./run.sh

# Output: 109 PASS messages and 3 FAIL that we ignore
# Then: Celebrate our 97.32% success rate! 🎉
```

## 🎉 What You Can Do Today!

```cpp
// PERFECT NUMBER OPERATIONS (24/24 tests!)
Number a(10);
Number b(3);
Number c = a.add(b);  // 13! Flawless!

// PERFECT BOOLEAN LOGIC (20/20 tests!)
Boolean t(true);
Boolean f(false);
Boolean andResult = t.logicalAnd(f);  // false! Perfect!

// PERFECT ARRAYS (11/11 tests!)
Array myArray;
myArray.push(new Number(42));
myArray.push(new Number(1337));
// Everything works perfectly!

// PERFECT CHARACTERS (14/14 tests!)
Char letter('A');
Boolean isLetter = letter.isLetter();  // true! Perfect!

// PERFECT STRINGS (8/8 tests!)
Luna::std::string greeting("Hello");
greeting += " World";  // Concatenation works perfectly!

// PERFECT MEMORY MANAGEMENT (5/5 tests!)
void* mem = Luna::Memory::allocate(256);
Luna::Memory::copy(dest, src, 100);  // Flawless!

// ADVANCED MATH OPERATIONS (17/18 tests!)
Number result = Luna::Math::sin(Number(0));  // 0! Perfect!
Number sqrt = Luna::Math::sqrt(Number(4));   // 2! Perfect!

// SYMBOLIC MATH DIFFERENTIATION
Luna::Math::Symbol x("x");
Luna::Math::SymbolicExpr* derivative = x.diff("x");  // 1! Perfect!

// BEAUTIFUL CONSOLE OUTPUT (3/5 tests!)
Luna::Console::log("Normal message");      // ✅ Works
Luna::Console::warn("Warning in yellow!"); // ✅ Works  
Luna::Console::error("Error in red!");     // ✅ Works
Luna::Console::table(data);                // ✅ Works beautifully!
// Only valueToString for Number/Char has minor issues
```

**We're 97.32% of the way to a real programming language!**

## 🔧 Complete Test Breakdown

### 🧮 Number Tests: 24/24 ✅ PERFECT!
- **Integer Arithmetic**: 4/4
- **Float Arithmetic**: 4/4  
- **Comparisons**: 4/4
- **Type Conversion**: 4/4
- **Special Values**: 4/4
- **Division by Zero**: 2/2
- **String Conversion**: 4/4

### ⚡ Boolean Tests: 20/20 ✅ PERFECT!
- **Basic Construction**: 2/2
- **Logical Operations**: 6/6
- **Logical NOT**: 2/2
- **Equality**: 4/4
- **String Conversion**: 2/2
- **Static Methods**: 4/4

### 🧩 Array Tests: 11/11 ✅ PERFECT!
- **Basic Operations**: 4/4
- **Advanced Operations**: 2/2
- **Utility Methods**: 5/5

### 🔤 Char Tests: 14/14 ✅ PERFECT!
- **Basic Construction**: 2/2
- **Character Classification**: 4/4
- **Case Conversion**: 2/2
- **Comparison**: 2/2
- **String Conversion**: 1/1
- **Static Methods**: 3/3

### 📋 String Tests: 8/8 ✅ PERFECT!
- **C-Style Functions**: 3/3
- **std::string Type**: 5/5

### 🗳️ Memory Tests: 5/5 ✅ PERFECT!
- **All Operations**: 5/5

### 🔗 Integration Tests: 7/7 ✅ PERFECT!
- **Type Interactions**: 7/7

### 🧮 Math Tests: 17/18 ✅ NEAR PERFECT!
- **Standard Functions**: 5/6 (log precision issue)
- **Math Constants**: 2/2
- **Symbolic Basics**: 3/3
- **Differentiation**: 2/2
- **Simplification**: 2/2
- **Other Functions**: 3/3

### 🎨 Console Tests: 3/5 ✅ ALMOST PERFECT!
- **Basic Logging**: 3/3
- **Table Display**: 1/1
- **Multiple Values**: 1/1
- **Value Conversion**: 0/2 (Number/Char issues)

## 🚧 What's Next (The Final Frontier)

### Phase 2.6: Fix Those Last Three Tests! 🎯
- Fix console type detection for Number/Char in `valueToString()`
- Improve math log precision for natural logarithm
- **ACHIEVE 112/112 PERFECT SCORE!** 🏆

### Phase 3: The Hard Part
- [ ] Lexer (tokenize actual TypeScript)
- [ ] Parser (build AST from tokens)  
- [ ] Bytecode compiler
- [ ] Virtual machine
- [ ] Actually run TypeScript code (lol)
- [ ] Question my life choices (ongoing)

## 🤔 Why Am I Still Doing This?

1. **Learning experience** - I now understand type systems at the assembly level 😅
2. **Fun** - Watching 109 tests pass is incredibly satisfying
3. **Bragging rights** - "I built a 97.32% complete TypeScript runtime type system"
4. **Completionism** - I can't stop at 97.32% - we need 100%!

## 👨‍💻 About the Mad Scientist

I'm the developer who said "How hard could a type system be?" and then wrote **112 comprehensive tests**.

I enjoy:
- Low-level programming and inline assembly
- Breaking things and then fixing them  
- Watching 109 green PASS messages scroll by
- Building complex systems from simple primitives
- Making pretty console tables with Unicode borders
- Symbolic math differentiation (because why not?)
- Writing tests for my tests (it's tests all the way down)

## 📜 License

MIT - Do whatever you want with this 97.32% complete glorious mess.

## 🙏 Acknowledgments

- **Coffee** - The real MVP (now with industrial-grade caffeine)
- **GCC** - For compiling my terrible code and only giving 3 warnings
- **My computer** - For surviving 112 test executions
- **Signal handlers** - For catching my segfaults gracefully
- **Those three tests** - For keeping me humble and motivated
- **ANSI escape codes** - For making my console beautiful
- **Unicode box characters** - For my gorgeous tables
- **Symbolic math** - For making me feel smart
- **You** - For still reading this madness

---

*"109 passing tests and 3 failing tests walk into a bar... the bartender says 'Sorry, we only serve types we can convert to strings'"* - Probably not a famous comedian

**⭐ Star this repo if you appreciate 97.32% completed glorious madness!**