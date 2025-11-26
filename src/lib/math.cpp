// src/lib/math.cpp
#include "math.hpp"
#include "../types/Number.hpp"
#include "../types/Array.hpp"
#include "../types/Strings.hpp"
#include "memory.hpp"
#include <cmath>
#include <cstdlib>
#include <cstdarg>

namespace Luna {
namespace Math {

// ===== MATHEMATICAL CONSTANTS =====
namespace constants {
    const double PI = 3.14159265358979323846;
    const double E = 2.71828182845904523536;
    const double LN2 = 0.693147180559945309417;
    const double LN10 = 2.30258509299404568402;
    const double SQRT2 = 1.41421356237309504880;
    const double SQRT1_2 = 0.70710678118654752440;
}

// ===== STANDARD MATH FUNCTIONS IMPLEMENTATION =====

// Helper function to access Number's private toDouble()
double numberToDouble(const Number& num) {
    // Since toDouble() is private, we'll use the public interface
    // For math functions, we'll work with the public methods
    if (num.isInt()) {
        return (double)num.toInt();
    } else {
        // For floats, we need to work around the private toDouble()
        // We'll use string conversion as a workaround for now
        char* str = num.toString();
        double result = 0.0;
        if (str) {
            // Simple string to double conversion
            bool negative = false;
            double value = 0.0;
            double fraction = 1.0;
            bool in_fraction = false;
            
            for (size_t i = 0; str[i] != '\0'; i++) {
                if (str[i] == '-') {
                    negative = true;
                } else if (str[i] == '.') {
                    in_fraction = true;
                } else if (str[i] >= '0' && str[i] <= '9') {
                    if (in_fraction) {
                        fraction *= 0.1;
                        value += (str[i] - '0') * fraction;
                    } else {
                        value = value * 10.0 + (str[i] - '0');
                    }
                }
            }
            
            result = negative ? -value : value;
            Memory::deallocate(str);
        }
        return result;
    }
}

Number sin(const Number& x) {
    // Use C standard library sin function
    return Number(::sin(numberToDouble(x)));
}

Number cos(const Number& x) {
    return Number(::cos(numberToDouble(x)));
}

Number tan(const Number& x) {
    return Number(::tan(numberToDouble(x)));
}

Number asin(const Number& x) {
    return Number(::asin(numberToDouble(x)));
}

Number acos(const Number& x) {
    return Number(::acos(numberToDouble(x)));
}

Number atan(const Number& x) {
    return Number(::atan(numberToDouble(x)));
}

Number atan2(const Number& y, const Number& x) {
    return Number(::atan2(numberToDouble(y), numberToDouble(x)));
}

Number sinh(const Number& x) {
    return Number(::sinh(numberToDouble(x)));
}

Number cosh(const Number& x) {
    return Number(::cosh(numberToDouble(x)));
}

Number tanh(const Number& x) {
    return Number(::tanh(numberToDouble(x)));
}

Number exp(const Number& x) {
    return Number(::exp(numberToDouble(x)));
}

Number log(const Number& x) {
    return Number(::log(numberToDouble(x)));
}

Number log10(const Number& x) {
    return Number(::log10(numberToDouble(x)));
}

Number log2(const Number& x) {
    return Number(::log2(numberToDouble(x)));
}

Number logBase(const Number& x, const Number& base) {
    return Number(::log(numberToDouble(x)) / ::log(numberToDouble(base)));
}

Number pow(const Number& base, const Number& exponent) {
    return Number(::pow(numberToDouble(base), numberToDouble(exponent)));
}

Number sqrt(const Number& x) {
    return Number(::sqrt(numberToDouble(x)));
}

Number cbrt(const Number& x) {
    return Number(::cbrt(numberToDouble(x)));
}

Number ceil(const Number& x) {
    return Number(::ceil(numberToDouble(x)));
}

Number floor(const Number& x) {
    return Number(::floor(numberToDouble(x)));
}

Number round(const Number& x) {
    return Number(::round(numberToDouble(x)));
}

Number trunc(const Number& x) {
    return Number(::trunc(numberToDouble(x)));
}

Number abs(const Number& x) {
    if (x.isInt()) {
        int32_t val = x.toInt();
        return Number(val < 0 ? -val : val);
    } else {
        // For floats, use the C standard library fabs
        return Number(::fabs(numberToDouble(x)));
    }
}

Number sign(const Number& x) {
    if (x.isInt()) {
        int32_t val = x.toInt();
        if (val > 0) return Number(1);
        if (val < 0) return Number(-1);
        return Number(0);
    } else {
        double val = numberToDouble(x);
        if (val > 0) return Number(1);
        if (val < 0) return Number(-1);
        return Number(0);
    }
}

Number min(const Number& a, const Number& b) {
    return a.lessThan(b) ? a : b;
}

Number max(const Number& a, const Number& b) {
    return a.greaterThan(b) ? a : b;
}

Number min(const Array& values) {
    if (values.isEmpty()) return Number::nan();
    
    Number* first = (Number*)values.get(0);
    Number min_val = *first;
    
    for (size_t i = 1; i < values.getLength(); i++) {
        Number* current = (Number*)values.get(i);
        if (current->lessThan(min_val)) {
            min_val = *current;
        }
    }
    
    return min_val;
}

Number max(const Array& values) {
    if (values.isEmpty()) return Number::nan();
    
    Number* first = (Number*)values.get(0);
    Number max_val = *first;
    
    for (size_t i = 1; i < values.getLength(); i++) {
        Number* current = (Number*)values.get(i);
        if (current->greaterThan(max_val)) {
            max_val = *current;
        }
    }
    
    return max_val;
}

Number random() {
    return Number((double)::rand() / RAND_MAX);
}

Number randomRange(const Number& min, const Number& max) {
    double min_val = numberToDouble(min);
    double max_val = numberToDouble(max);
    double range = max_val - min_val;
    return Number(min_val + random().toInt() * range);
}

// ===== SYMBOLIC EXPRESSION IMPLEMENTATIONS =====

// Symbol implementation
Symbol::Symbol(const char* var_name) {
    name = string::duplicate(var_name);
}

Symbol::Symbol(const Symbol& other) {
    name = string::duplicate(other.name);
}

Symbol::~Symbol() {
    if (name) {
        string::free(name);
    }
}

Number Symbol::evaluate(const Array& variables) const {
    // Look for variable value in the provided array
    for (size_t i = 0; i < variables.getLength(); i += 2) {
        Symbol* var = (Symbol*)variables.get(i);
        if (var && string::compare(var->getName(), name) == 0) {
            Number* value = (Number*)variables.get(i + 1);
            return *value;
        }
    }
    
    // Variable not found, return 0 as default
    return Number(0);
}

char* Symbol::toString() const {
    return string::duplicate(name);
}

SymbolicExpr* Symbol::diff(const char* variable) const {
    if (string::compare(name, variable) == 0) {
        return new Constant(Number(1));
    } else {
        return new Constant(Number(0));
    }
}

SymbolicExpr* Symbol::simplify() const {
    return new Symbol(*this);
}

bool Symbol::isConstant() const {
    return false;
}

SymbolicExpr* Symbol::copy() const {
    return new Symbol(*this);
}

// Constant implementation
Constant::Constant(const Number& val) : value(val) {}
Constant::Constant(double val) : value(val) {}
Constant::Constant(int val) : value(val) {}

Number Constant::evaluate(const Array& variables) const {
    return value;
}

char* Constant::toString() const {
    return value.toString();
}

SymbolicExpr* Constant::diff(const char* variable) const {
    return new Constant(Number(0));
}

SymbolicExpr* Constant::simplify() const {
    return new Constant(value);
}

bool Constant::isConstant() const {
    return true;
}

SymbolicExpr* Constant::copy() const {
    return new Constant(value);
}

// BinaryOp implementation
BinaryOp::BinaryOp(Operation operation, SymbolicExpr* lhs, SymbolicExpr* rhs) 
    : op(operation), left(lhs), right(rhs) {}

BinaryOp::~BinaryOp() {
    if (left) symbolic::free(left);
    if (right) symbolic::free(right);
}

Number BinaryOp::evaluate(const Array& variables) const {
    Number left_val = left->evaluate(variables);
    Number right_val = right->evaluate(variables);
    
    switch (op) {
        case Operation::ADD:
            return left_val.add(right_val);
        case Operation::SUBTRACT:
            return left_val.subtract(right_val);
        case Operation::MULTIPLY:
            return left_val.multiply(right_val);
        case Operation::DIVIDE:
            return left_val.divide(right_val);
        case Operation::POWER:
            return pow(left_val, right_val);
        default:
            return Number::nan();
    }
}

char* BinaryOp::toString() const {
    char* left_str = left->toString();
    char* right_str = right->toString();
    
    const char* op_str = "";
    switch (op) {
        case Operation::ADD: op_str = " + "; break;
        case Operation::SUBTRACT: op_str = " - "; break;
        case Operation::MULTIPLY: op_str = " * "; break;
        case Operation::DIVIDE: op_str = " / "; break;
        case Operation::POWER: op_str = " ^ "; break;
    }
    
    char* result = string::concatenate(left_str, op_str);
    char* full_result = string::concatenate(result, right_str);
    
    string::free(left_str);
    string::free(right_str);
    string::free(result);
    
    return full_result;
}

SymbolicExpr* BinaryOp::diff(const char* variable) const {
    SymbolicExpr* left_diff = left->diff(variable);
    SymbolicExpr* right_diff = right->diff(variable);
    
    switch (op) {
        case Operation::ADD:
        case Operation::SUBTRACT: {
            BinaryOp::Operation new_op = (op == Operation::ADD) ? 
                BinaryOp::Operation::ADD : BinaryOp::Operation::SUBTRACT;
            return new BinaryOp(new_op, left_diff, right_diff);
        }
        
        case Operation::MULTIPLY: {
            // Product rule: (fg)' = f'g + fg'
            SymbolicExpr* term1 = new BinaryOp(
                BinaryOp::Operation::MULTIPLY, left_diff, right->copy());
            SymbolicExpr* term2 = new BinaryOp(
                BinaryOp::Operation::MULTIPLY, left->copy(), right_diff);
            return new BinaryOp(BinaryOp::Operation::ADD, term1, term2);
        }
        
        case Operation::DIVIDE: {
            // Quotient rule: (f/g)' = (f'g - fg') / g²
            SymbolicExpr* numerator1 = new BinaryOp(
                BinaryOp::Operation::MULTIPLY, left_diff, right->copy());
            SymbolicExpr* numerator2 = new BinaryOp(
                BinaryOp::Operation::MULTIPLY, left->copy(), right_diff);
            SymbolicExpr* numerator = new BinaryOp(
                BinaryOp::Operation::SUBTRACT, numerator1, numerator2);
            SymbolicExpr* denominator = new BinaryOp(
                BinaryOp::Operation::POWER, right->copy(), new Constant(Number(2)));
            return new BinaryOp(BinaryOp::Operation::DIVIDE, numerator, denominator);
        }
        
        case Operation::POWER: {
            // Power rule and exponential rule
            if (right->isConstant()) {
                // Power rule: (x^n)' = n*x^(n-1)
                Constant* exponent = dynamic_cast<Constant*>(right);
                if (exponent) {
                    Number new_exp_val = exponent->getValue().subtract(Number(1));
                    SymbolicExpr* new_exp = new Constant(new_exp_val);
                    SymbolicExpr* power_part = new BinaryOp(
                        BinaryOp::Operation::POWER, left->copy(), new_exp);
                    SymbolicExpr* coefficient = new BinaryOp(
                        BinaryOp::Operation::MULTIPLY, right->copy(), power_part);
                    return new BinaryOp(
                        BinaryOp::Operation::MULTIPLY, coefficient, left_diff);
                }
            }
            // General case: use placeholder
            return new Constant(Number(0));
        }
        
        default:
            return new Constant(Number(0));
    }
}

SymbolicExpr* BinaryOp::simplify() const {
    return Simplifier::simplify(this);
}

bool BinaryOp::isConstant() const {
    return left->isConstant() && right->isConstant();
}

SymbolicExpr* BinaryOp::copy() const {
    return new BinaryOp(op, left->copy(), right->copy());
}

// FunctionCall implementation
FunctionCall::FunctionCall(Function function, SymbolicExpr* arg) 
    : func(function), argument(arg) {}

FunctionCall::~FunctionCall() {
    if (argument) symbolic::free(argument);
}

Number FunctionCall::evaluate(const Array& variables) const {
    Number arg_val = argument->evaluate(variables);
    
    switch (func) {
        case Function::SIN: return sin(arg_val);
        case Function::COS: return cos(arg_val);
        case Function::TAN: return tan(arg_val);
        case Function::EXP: return exp(arg_val);
        case Function::LOG: return log(arg_val);
        case Function::SQRT: return sqrt(arg_val);
        default: return Number::nan();
    }
}

char* FunctionCall::toString() const {
    char* arg_str = argument->toString();
    
    const char* func_name = "";
    switch (func) {
        case Function::SIN: func_name = "sin"; break;
        case Function::COS: func_name = "cos"; break;
        case Function::TAN: func_name = "tan"; break;
        case Function::EXP: func_name = "exp"; break;
        case Function::LOG: func_name = "log"; break;
        case Function::SQRT: func_name = "sqrt"; break;
    }
    
    char* func_part = string::concatenate(func_name, "(");
    char* result = string::concatenate(func_part, arg_str);
    char* full_result = string::concatenate(result, ")");
    
    string::free(arg_str);
    string::free(func_part);
    string::free(result);
    
    return full_result;
}

SymbolicExpr* FunctionCall::diff(const char* variable) const {
    SymbolicExpr* arg_diff = argument->diff(variable);
    
    switch (func) {
        case Function::SIN: {
            // d/dx sin(u) = cos(u) * du/dx
            SymbolicExpr* cos_call = new FunctionCall(Function::COS, argument->copy());
            return new BinaryOp(BinaryOp::Operation::MULTIPLY, cos_call, arg_diff);
        }
        case Function::COS: {
            // d/dx cos(u) = -sin(u) * du/dx
            SymbolicExpr* sin_call = new FunctionCall(Function::SIN, argument->copy());
            SymbolicExpr* neg_one = new Constant(Number(-1));
            SymbolicExpr* neg_sin = new BinaryOp(BinaryOp::Operation::MULTIPLY, neg_one, sin_call);
            return new BinaryOp(BinaryOp::Operation::MULTIPLY, neg_sin, arg_diff);
        }
        case Function::EXP: {
            // d/dx exp(u) = exp(u) * du/dx
            SymbolicExpr* exp_call = new FunctionCall(Function::EXP, argument->copy());
            return new BinaryOp(BinaryOp::Operation::MULTIPLY, exp_call, arg_diff);
        }
        case Function::LOG: {
            // d/dx log(u) = (1/u) * du/dx
            SymbolicExpr* one = new Constant(Number(1));
            SymbolicExpr* reciprocal = new BinaryOp(BinaryOp::Operation::DIVIDE, one, argument->copy());
            return new BinaryOp(BinaryOp::Operation::MULTIPLY, reciprocal, arg_diff);
        }
        case Function::SQRT: {
            // d/dx sqrt(u) = (1/(2*sqrt(u))) * du/dx
            SymbolicExpr* one = new Constant(Number(1));
            SymbolicExpr* two = new Constant(Number(2));
            SymbolicExpr* sqrt_call = new FunctionCall(Function::SQRT, argument->copy());
            SymbolicExpr* denominator = new BinaryOp(BinaryOp::Operation::MULTIPLY, two, sqrt_call);
            SymbolicExpr* reciprocal = new BinaryOp(BinaryOp::Operation::DIVIDE, one, denominator);
            return new BinaryOp(BinaryOp::Operation::MULTIPLY, reciprocal, arg_diff);
        }
        default:
            return new Constant(Number(0));
    }
}

SymbolicExpr* FunctionCall::simplify() const {
    return Simplifier::simplify(this);
}

bool FunctionCall::isConstant() const {
    return argument->isConstant();
}

SymbolicExpr* FunctionCall::copy() const {
    return new FunctionCall(func, argument->copy());
}

// Simplifier implementation
SymbolicExpr* Simplifier::simplify(const SymbolicExpr* expr) {
    if (!expr) return nullptr;
    
    // Use dynamic_cast to check types safely
    if (dynamic_cast<const BinaryOp*>(expr)) {
        return simplifyBinaryOp(static_cast<const BinaryOp*>(expr));
    } else if (dynamic_cast<const Constant*>(expr)) {
        return simplifyConstant(static_cast<const Constant*>(expr));
    } else if (dynamic_cast<const Symbol*>(expr)) {
        return simplifySymbol(static_cast<const Symbol*>(expr));
    } else if (dynamic_cast<const FunctionCall*>(expr)) {
        return simplifyFunctionCall(static_cast<const FunctionCall*>(expr));
    }
    
    return expr->copy();
}

SymbolicExpr* Simplifier::simplifyBinaryOp(const BinaryOp* expr) {
    SymbolicExpr* left_simple = simplify(expr->getLeft());
    SymbolicExpr* right_simple = simplify(expr->getRight());
    
    // If both sides are constants, evaluate
    if (left_simple->isConstant() && right_simple->isConstant()) {
        Array empty_vars;
        Number result = expr->evaluate(empty_vars);
        symbolic::free(left_simple);
        symbolic::free(right_simple);
        return new Constant(result);
    }
    
    BinaryOp::Operation op = expr->getOperation();
    
    // Algebraic simplification rules
    switch (op) {
        case BinaryOp::Operation::ADD: {
            Constant* left_const = dynamic_cast<Constant*>(left_simple);
            Constant* right_const = dynamic_cast<Constant*>(right_simple);
            
            // x + 0 → x
            if (right_const && right_const->getValue().equals(Number(0))) {
                symbolic::free(right_simple);
                return left_simple;
            }
            // 0 + x → x
            if (left_const && left_const->getValue().equals(Number(0))) {
                symbolic::free(left_simple);
                return right_simple;
            }
            break;
        }
        
        case BinaryOp::Operation::MULTIPLY: {
            Constant* left_const = dynamic_cast<Constant*>(left_simple);
            Constant* right_const = dynamic_cast<Constant*>(right_simple);
            
            // x * 0 → 0
            if ((left_const && left_const->getValue().equals(Number(0))) ||
                (right_const && right_const->getValue().equals(Number(0)))) {
                symbolic::free(left_simple);
                symbolic::free(right_simple);
                return new Constant(Number(0));
            }
            // x * 1 → x
            if (right_const && right_const->getValue().equals(Number(1))) {
                symbolic::free(right_simple);
                return left_simple;
            }
            // 1 * x → x
            if (left_const && left_const->getValue().equals(Number(1))) {
                symbolic::free(left_simple);
                return right_simple;
            }
            break;
        }
        
        case BinaryOp::Operation::POWER: {
            Constant* right_const = dynamic_cast<Constant*>(right_simple);
            
            // x^0 → 1
            if (right_const && right_const->getValue().equals(Number(0))) {
                symbolic::free(left_simple);
                symbolic::free(right_simple);
                return new Constant(Number(1));
            }
            // x^1 → x
            if (right_const && right_const->getValue().equals(Number(1))) {
                symbolic::free(right_simple);
                return left_simple;
            }
            break;
        }
        
        default:
            break;
    }
    
    return new BinaryOp(op, left_simple, right_simple);
}

SymbolicExpr* Simplifier::simplifyConstant(const Constant* expr) {
    return expr->copy(); // Constants are already simplified
}

SymbolicExpr* Simplifier::simplifySymbol(const Symbol* expr) {
    return expr->copy(); // Symbols are already simplified
}

SymbolicExpr* Simplifier::simplifyFunctionCall(const FunctionCall* expr) {
    SymbolicExpr* arg_simple = simplify(expr->getArgument());
    
    // If argument is constant, evaluate the function
    if (arg_simple->isConstant()) {
        Array empty_vars;
        Number result = expr->evaluate(empty_vars);
        symbolic::free(arg_simple);
        return new Constant(result);
    }
    
    return new FunctionCall(expr->getFunction(), arg_simple);
}

// Symbolic utilities implementation
namespace symbolic {
    Array* symbols(const char* names...) {
        Array* result = new Array();
        
        va_list args;
        va_start(args, names);
        
        const char* current = names;
        while (current) {
            result->push(new Symbol(current));
            current = va_arg(args, const char*);
        }
        
        va_end(args);
        return result;
    }
    
    SymbolicExpr* diff(SymbolicExpr* expr, const char* variable) {
        if (!expr) return nullptr;
        return expr->diff(variable);
    }
    
    void free(SymbolicExpr* expr) {
        if (expr) {
            delete expr;
        }
    }
}

} // namespace Math
} // namespace Luna