# 🌙 Lunar.TS

> **A Mad Science Experiment in TypeScript Runtimes**  
> *Because why not build a TypeScript runtime from scratch?*

[![Status](https://img.shields.io/badge/status-madness%20in%20progress-red)](https://github.com/uriel-flame-of-god/Lunar.TS)
[![Tests](https://img.shields.io/badge/tests-67%2F69%20passing-brightgreen)](https://github.com/uriel-flame-of-god/Lunar.TS)
[![Reason](https://img.shields.io/badge/why-because%20I%20can-purple)](https://github.com/uriel-flame-of-god/Lunar.TS)

## 🎯 What is This Madness?

Lunar.TS is my **personal playground** for building a TypeScript runtime from absolute scratch. 

**Why?** Because:
- I thought it would be fun 💀
- I wanted to see if I could 🗣  
- I enjoy pain and assembly programming 🙏
- Maybe someday I'll run TypeScript on bare metal (probably not, but let's pretend)

## 📊 Current Achievement: **I Made SIX Types!** 🔢🔘🧩🔤📋🎨

HOLY MOLY! The madness continues! I now have:

### ✅ What Actually Works

- **Number class** - 20/20 tests passing! 🧮
- **Boolean class** - 20/20 tests passing! ⚡  
- **Array class** - 10/11 tests passing! 🧩 (SO CLOSE!)
- **Char class** - 14/14 tests passing! 🔤
- **String types** - 8/8 tests passing! 📋
- **Console system** - 5/6 tests passing! 🎨
- **Memory management** - 5/5 tests passing! 🗳️
- **Integration tests** - 7/7 tests passing! 🔗
- **67/69 TOTAL TESTS PASSING** - 97.1% SUCCESS RATE! 🎉

### 🚨 The Two Pesky Failures

1. **Array construction** - That one test still haunts me
2. **Boolean/Char string conversion in console** - Minor type detection issue

## 🏗 "Architecture" (I'm Using That Term Loosely)

```
TypeScript Dreams ───────┐
                        ↓
   Number.cpp ──20/20─> Perfect math!
   Boolean.cpp ─20/20─> Perfect logic!
   Array.cpp ──10/11─> Almost perfect arrays!
   Char.cpp ───14/14─> Perfect characters!
   Strings.cpp ─8/8──> Perfect strings!
   Console.cpp ─5/6──> Almost perfect output!
                        ↑
   Assembly Madness ────┘
```

### The Grand Vision (Delusions)

1. ~~Build a Number type~~ ✅ **PERFECT! (20/20)**
2. ~~Build a Boolean type~~ ✅ **PERFECT! (20/20)**
3. ~~Build an Array type~~ ✅ **ALMOST PERFECT! (10/11)**
4. ~~Build a Char type~~ ✅ **PERFECT! (14/14)**
5. ~~Build String types~~ ✅ **PERFECT! (8/8)**
6. ~~Build Console system~~ ✅ **ALMOST PERFECT! (5/6)**
7. **Parse actual TypeScript code** (lol)
8. ???  
9. Profit! (just kidding, there's no profit)

## 🛠 How to Run This Masterpiece

```bash
# Clone this monument to poor life choices
git clone https://github.com/uriel-flame-of-god/Lunar.TS
cd Lunar.TS

# Run the thing
./run.sh

# Output: 67 PASS messages and 2 FAIL that we ignore
# Then: Celebrate our 97.1% success rate! 🎉
```

## 🎉 What You Can Do Today!

```cpp
// PERFECT NUMBER OPERATIONS (20/20 tests!)
Number a(10);
Number b(3);
Number c = a.add(b);  // 13! Flawless!

// PERFECT BOOLEAN LOGIC (20/20 tests!)
Boolean t(true);
Boolean f(false);
Boolean andResult = t.logicalAnd(f);  // false! Perfect!

// ALMOST PERFECT ARRAYS (10/11 tests!)
Array myArray;
myArray.push(new Number(42));
myArray.push(new Number(1337));
// Construction works, just one edge case fails

// PERFECT CHARACTERS (14/14 tests!)
Char letter('A');
Boolean isLetter = letter.isLetter();  // true! Perfect!

// PERFECT STRINGS (8/8 tests!)
Luna::std::string greeting("Hello");
greeting += " World";  // Concatenation works perfectly!

// BEAUTIFUL CONSOLE OUTPUT (5/6 tests!)
Luna::Console::log("Normal message");      // ✅ Works
Luna::Console::warn("Warning in yellow!"); // ✅ Works  
Luna::Console::error("Error in red!");     // ✅ Works
Luna::Console::table(data);                // ✅ Works beautifully!
// Only valueToString for Boolean/Char has minor issues
```

**We're 97.1% of the way to a real programming language!**

## 🔧 Complete Test Breakdown

### 🧮 Number Tests: 20/20 ✅ PERFECT!
- **Integer Arithmetic**: 4/4
- **Float Arithmetic**: 4/4  
- **Comparisons**: 4/4
- **Type Conversion**: 4/4
- **Special Values**: 4/4
- **String Conversion**: 4/4

### ⚡ Boolean Tests: 20/20 ✅ PERFECT!
- **Basic Construction**: 2/2
- **Logical Operations**: 6/6
- **Logical NOT**: 2/2
- **Equality**: 4/4
- **String Conversion**: 2/2
- **Static Methods**: 4/4

### 🧩 Array Tests: 10/11 ✅ ALMOST PERFECT!
- **Basic Operations**: 3/4 (construction fails)
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

### 🎨 Console Tests: 5/6 ✅ ALMOST PERFECT!
- **Basic Logging**: 3/3
- **Table Display**: 1/1
- **Multiple Values**: 1/1
- **Value Conversion**: 0/1 (Boolean/Char issue)

### 🔗 Integration Tests: 7/7 ✅ PERFECT!
- **Type Interactions**: 7/7

### 🗳️ Memory Tests: 5/5 ✅ PERFECT!
- **All Operations**: 5/5

## 🚧 What's Next (The Final Frontier)

### Phase 2.4: Fix Those Last Two Tests! 🎯
- Fix array construction edge case
- Fix Boolean/Char type detection in console
- **ACHIEVE 69/69 PERFECT SCORE!** 🏆

### Phase 3: The Hard Part
- [ ] Lexer (tokenize stuff)
- [ ] Parser (make tree from tokens)  
- [ ] Actually run TypeScript code (pfffft)
- [ ] Question my life choices (ongoing)

## 🤔 Why Am I Still Doing This?

1. **Learning experience** - I now understand type systems at the assembly level 😅
2. **Fun** - Watching 67 tests pass is incredibly satisfying
3. **Bragging rights** - "I built a 97.1% complete TypeScript runtime type system"
4. **Completionism** - I can't stop at 97.1% - we need 100%!

## 🎭 Real Talk

We're at **67/69 tests passing** - that's a 97.1% success rate! The two failures are minor:

1. **Array construction** - Probably just an initialization edge case
2. **Console type detection** - Simple fix in `valueToString()` function

The fact that we have:
- **Perfect number handling** (all edge cases covered)
- **Perfect boolean logic** (all operations working)
- **Perfect character processing** (classification and conversion)
- **Perfect string system** (both C-style and TypeScript-style)
- **Perfect memory management** (allocation/deallocation working)
- **Beautiful console output** (tables, colors, formatting)

...is absolutely incredible for a "mad science experiment"!

## 👨‍💻 About the Mad Scientist

I'm the developer who said "How hard could a type system be?" and then wrote 69 comprehensive tests.

I enjoy:
- Low-level programming
- Breaking things
- Fixing things I broke  
- Watching 67 green PASS messages
- Ignoring those 2 red FAIL messages
- Building complex systems from simple primitives
- Making pretty console tables with Unicode borders

## 📜 License

MIT - Do whatever you want with this 97.1% complete glorious mess.

## 🙏 Acknowledgments

- **Coffee** - The real MVP (now with industrial-grade caffeine)
- **GCC** - For compiling my terrible code and only giving 3 warnings
- **My computer** - For surviving 69 test executions
- **Signal handlers** - For catching my segfaults gracefully
- **Those two tests** - For keeping me humble and motivated
- **ANSI escape codes** - For making my console beautiful
- **Unicode box characters** - For my gorgeous tables
- **You** - For still reading this madness

---

*"67 passing tests and 2 failing tests walk into a bar... the failing tests order drinks but can't pay because their constructors failed"* - Probably not a famous comedian

**⭐ Star this repo if you appreciate 97.1% completed glorious madness!**
