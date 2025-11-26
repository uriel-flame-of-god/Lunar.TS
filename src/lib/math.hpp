// src/lib/math.hpp
#pragma once

#include "../types/Number.hpp"
#include "../types/Array.hpp"
#include "memory.hpp"
#include <cmath>

namespace Luna {
namespace Math {

// ===== STANDARD MATH FUNCTIONS =====

/**
 * @brief Mathematical constants
 */
namespace constants {
    extern const double PI;
    extern const double E;
    extern const double LN2;
    extern const double LN10;
    extern const double SQRT2;
    extern const double SQRT1_2;
}

/**
 * @brief Trigonometric functions
 */
Number sin(const Number& x);
Number cos(const Number& x);
Number tan(const Number& x);
Number asin(const Number& x);
Number acos(const Number& x);
Number atan(const Number& x);
Number atan2(const Number& y, const Number& x);

/**
 * @brief Hyperbolic functions
 */
Number sinh(const Number& x);
Number cosh(const Number& x);
Number tanh(const Number& x);

/**
 * @brief Exponential and logarithmic functions
 */
Number exp(const Number& x);
Number log(const Number& x);  // Natural logarithm
Number log10(const Number& x); // Base-10 logarithm
Number log2(const Number& x);  // Base-2 logarithm
Number logBase(const Number& x, const Number& base);

/**
 * @brief Power functions
 */
Number pow(const Number& base, const Number& exponent);
Number sqrt(const Number& x);
Number cbrt(const Number& x);

/**
 * @brief Rounding functions
 */
Number ceil(const Number& x);
Number floor(const Number& x);
Number round(const Number& x);
Number trunc(const Number& x);

/**
 * @brief Absolute value and sign
 */
Number abs(const Number& x);
Number sign(const Number& x);

/**
 * @brief Minimum and maximum
 */
Number min(const Number& a, const Number& b);
Number max(const Number& a, const Number& b);
Number min(const Array& values);
Number max(const Array& values);

/**
 * @brief Random number generation
 */
Number random();
Number randomRange(const Number& min, const Number& max);

// ===== SYMBOLIC MATH SYSTEM =====

/**
 * @brief Base class for all symbolic expressions
 */
class SymbolicExpr {
public:
    virtual ~SymbolicExpr() = default;
    
    /**
     * @brief Evaluate expression with given variable values
     */
    virtual Number evaluate(const Array& variables = Array()) const = 0;
    
    /**
     * @brief Get string representation
     */
    virtual char* toString() const = 0;
    
    /**
     * @brief Differentiate with respect to variable
     */
    virtual SymbolicExpr* diff(const char* variable) const = 0;
    
    /**
     * @brief Simplify the expression
     */
    virtual SymbolicExpr* simplify() const = 0;
    
    /**
     * @brief Check if expression is constant
     */
    virtual bool isConstant() const = 0;
    
    /**
     * @brief Copy the expression
     */
    virtual SymbolicExpr* copy() const = 0;
};

/**
 * @brief Symbolic variable
 */
class Symbol : public SymbolicExpr {
private:
    char* name;
    
public:
    Symbol(const char* var_name);
    Symbol(const Symbol& other);
    ~Symbol();
    
    Number evaluate(const Array& variables) const override;
    char* toString() const override;
    SymbolicExpr* diff(const char* variable) const override;
    SymbolicExpr* simplify() const override;
    bool isConstant() const override;
    SymbolicExpr* copy() const override;
    
    const char* getName() const { return name; }
};

/**
 * @brief Numeric constant
 */
class Constant : public SymbolicExpr {
private:
    Number value;
    
public:
    Constant(const Number& val);
    Constant(double val);
    Constant(int val);
    
    Number evaluate(const Array& variables) const override;
    char* toString() const override;
    SymbolicExpr* diff(const char* variable) const override;
    SymbolicExpr* simplify() const override;
    bool isConstant() const override;
    SymbolicExpr* copy() const override;
    
    Number getValue() const { return value; }
};

/**
 * @brief Binary operation expression
 */
class BinaryOp : public SymbolicExpr {
public:
    enum class Operation {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        POWER
    };
    
private:
    Operation op;
    SymbolicExpr* left;
    SymbolicExpr* right;
    
public:
    BinaryOp(Operation operation, SymbolicExpr* lhs, SymbolicExpr* rhs);
    ~BinaryOp();
    
    Number evaluate(const Array& variables) const override;
    char* toString() const override;
    SymbolicExpr* diff(const char* variable) const override;
    SymbolicExpr* simplify() const override;
    bool isConstant() const override;
    SymbolicExpr* copy() const override;
    
    Operation getOperation() const { return op; }
    SymbolicExpr* getLeft() const { return left; }
    SymbolicExpr* getRight() const { return right; }
};

/**
 * @brief Function call expression
 */
class FunctionCall : public SymbolicExpr {
public:
    enum class Function {
        SIN,
        COS,
        TAN,
        EXP,
        LOG,
        SQRT
    };
    
private:
    Function func;
    SymbolicExpr* argument;
    
public:
    FunctionCall(Function function, SymbolicExpr* arg);
    ~FunctionCall();
    
    Number evaluate(const Array& variables) const override;
    char* toString() const override;
    SymbolicExpr* diff(const char* variable) const override;
    SymbolicExpr* simplify() const override;
    bool isConstant() const override;
    SymbolicExpr* copy() const override;
    
    Function getFunction() const { return func; }
    SymbolicExpr* getArgument() const { return argument; }
};

/**
 * @brief Algebraic simplifier
 */
class Simplifier {
public:
    /**
     * @brief Simplify symbolic expression
     */
    static SymbolicExpr* simplify(const SymbolicExpr* expr);
    
private:
    static SymbolicExpr* simplifyBinaryOp(const BinaryOp* expr);
    static SymbolicExpr* simplifyConstant(const Constant* expr);
    static SymbolicExpr* simplifySymbol(const Symbol* expr);
    static SymbolicExpr* simplifyFunctionCall(const FunctionCall* expr);
};

/**
 * @brief Symbolic math utilities
 */
namespace symbolic {
    /**
     * @brief Create symbolic variables
     */
    Array* symbols(const char* names...);
    
    /**
     * @brief Differentiate expression
     */
    SymbolicExpr* diff(SymbolicExpr* expr, const char* variable);
    
    /**
     * @brief Free symbolic expression memory
     */
    void free(SymbolicExpr* expr);
}

} // namespace Math
} // namespace Luna