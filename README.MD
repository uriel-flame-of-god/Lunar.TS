# 🌙 Lunar.TS

> **A Mad Science Experiment in TypeScript Runtimes**  
> *Because why not build a TypeScript runtime from scratch?*

[![Status](https://img.shields.io/badge/status-madness%20in%20progress-red)](https://github.com/uriel-archangel-of-god/Lunar.TS)
[![Tests](https://img.shields.io/badge/tests-50%2F50%20passing-brightgreen)](https://github.com/uriel-archangel-of-god/Lunar.TS)
[![Reason](https://img.shields.io/badge/why-because%20I%20can-purple)](https://github.com/uriel-archangel-of-god/Lunar.TS)

## 🎯 What is This Madness?

Lunar.TS is my **personal playground** for building a TypeScript runtime from absolute scratch. 

**Why?** Because:
- I thought it would be fun 💀
- I wanted to see if I could 🗣  
- I enjoy pain and assembly programming 🙏
- Maybe someday I'll run TypeScript on bare metal (probably not, but let's pretend)

## 📊 Current Achievement: **I Made TWO Types!** 🔢🔘

Yes, you read that right. After more weeks of work, I have successfully created:

### ✅ What Actually Works

- **A Number class** that can do math (woohoo! 🎉)
- **A Boolean class** that can do logic (true/false, so complex! 🧠)
- **Memory allocator** that mostly doesn't segfault anymore
- **50/50 tests passing** for arithmetic AND logic operations
- **Crash protection** that recovers from segfaults (black magic 🪄)
- **String conversion** that actually works now (mostly)

### 🚨 What Definitely Doesn't Work

- Everything else
- My sleep schedule
- Any actual TypeScript code
- My social life (still)

## 🏗 "Architecture" (I'm Using That Term Loosely)

```
TypeScript Dreams ───────┐
                        ↓
   Reality: Number.cpp ──> "It compiles!" ──> Actually works!
   Reality: Boolean.cpp ──> "It compiles!" ──> Also works!  
                        ↑
   Assembly Madness ────┘
```

### The Grand Vision (Delusions)

1. ~~Build a Number type~~ ✅ **DONE!**
2. ~~Build a Boolean type~~ ✅ **DONE!**
3. Make them talk to each other ✅ **DONE!**
4. Parse actual TypeScript code (lol)
5. ???  
6. Profit! (just kidding, there's no profit)

## 🛠 How to Run This Masterpiece

```bash
# Clone this monument to poor life choices
git clone https://github.com/uriel-archangel-of-god/Lunar.TS
cd Lunar.TS

# Run the thing
./run.sh

# Output: 50 PASS messages for Number AND Boolean tests
# Then: No segfaults! (usually... mostly... sometimes)
```

## 🎉 What You Can Do Today!

```cpp
// Behold! I can create numbers!
Number a(10);
Number b(3);
Number c = a.add(b);  // It's 13! MIRACLES!

// I can even divide by zero!
Number infinity = a.divide(Number(0));  // 🤯

// AND NOW I CAN DO LOGIC!
Boolean t(true);
Boolean f(false);
Boolean result = t.logicalAnd(f);  // false! SO SMART!

// They even work together!
Number x(10);
Number y(20);
Boolean comparison = Boolean(x.lessThan(y));  // true! MIND BLOWN!
```

**Groundbreaking, I know.**

## 🔧 What I Fixed Since Last Time

- **Memory allocator** - No more double-counting allocations
- **String conversion** - Actually allocates memory properly now  
- **Crash recovery** - Segfaults don't kill the whole test suite
- **Assembly instructions** - Less likely to explode your CPU

## 🚧 What's Actually Next (No Really)

### Phase 2: More Types I Guess

- [x] ~~Fix string segfault~~ ✅ **FIXED!**
- [x] ~~Boolean type~~ ✅ **DONE!**
- [ ] String type (if I feel brave)
- [ ] Array type (stretch goal)

### Phase 3: The Hard Part

- [ ] Lexer (tokenize stuff)
- [ ] Parser (make tree from tokens)  
- [ ] Actually run TypeScript code (pfffft)
- [ ] Question my life choices

## 🤔 Why Am I Really Doing This?

1. **Learning experience** - I'm learning a ton about compilers and runtime design
2. **Fun** - Assembly programming is weirdly satisfying
3. **Bragging rights** - "I built a TypeScript runtime" sounds cool
4. **Maybe eventually** - A minimal TS runtime for embedded systems?

## 🎭 Real Talk

This is a **hobby project** with no deadlines, no pressure, and no expectations. I'm building it because I enjoy the challenge and want to understand how programming languages work at the deepest level.

Progress is slow. Code is messy. But I'm learning. And now I have TWO whole types!

## 👨‍💻 About the Mad Scientist

I'm just a developer who thought "how hard could it be?" and then found out. 

I enjoy:
- Low-level programming
- Breaking things
- Fixing things I broke
- Making Boolean types that can do AND/OR/NOT operations
- Repeat

## 📜 License

MIT - Do whatever you want with this glorious mess.

## 🙏 Acknowledgments

- **Coffee** - The real MVP
- **GCC** - For not judging my terrible code
- **My computer** - For not exploding yet
- **Signal handlers** - For catching my segfaults like a safety net
- **You** - For reading this far into my madness

---

*"Any sufficiently advanced technology is indistinguishable from a rigged demo."* - Probably not Arthur C. Clarke

**⭐ Star this repo if you appreciate terrible life choices!**
