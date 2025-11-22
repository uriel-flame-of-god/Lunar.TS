#pragma once

typedef unsigned char uint8_t;
typedef int int32_t;

class Number {
private:
    uint8_t type_tag;
    union {
        int32_t int_val;
        double float_val;
    };

public:
    /**
     * @brief Construct integer number
     */
    Number(int32_t value);
    
    /**
     * @brief Construct double number
     */
    Number(double value);
    
    /**
     * @brief Add two numbers
     */
    Number add(const Number& other) const;
    
    /**
     * @brief Subtract two numbers
     */
    Number subtract(const Number& other) const;
    
    /**
     * @brief Multiply two numbers
     */
    Number multiply(const Number& other) const;
    
    /**
     * @brief Divide two numbers (handles div by zero)
     */
    Number divide(const Number& other) const;
    
    /**
     * @brief Check equality
     */
    bool equals(const Number& other) const;
    
    /**
     * @brief Check less than
     */
    bool lessThan(const Number& other) const;
    
    /**
     * @brief Check greater than
     */
    bool greaterThan(const Number& other) const;
    
    /**
     * @brief Convert to boolean (0/NaN = false)
     */
    bool toBoolean() const;
    
    /**
     * @brief Convert to string (caller manages memory)
     */
    char* toString() const;
    
    /**
     * @brief Create NaN value
     */
    static Number nan();
    
    /**
     * @brief Create positive infinity
     */
    static Number infinity();
    
    /**
     * @brief Create negative infinity
     */
    static Number negativeInfinity();
    
    /**
     * @brief Check if integer type
     */
    bool isInt() const;
    
    /**
     * @brief Check if float type
     */
    bool isFloat() const;
    
    /**
     * @brief Check if value is NaN
     */
    bool isNaN() const;
    
    /**
     * @brief Check if value is infinity
     */
    bool isInfinity() const;
    
private:
    double toDouble() const;
    void intToString(int32_t value, char* buffer) const;
    void doubleToString(double value, char* buffer) const;
};