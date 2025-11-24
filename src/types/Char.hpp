#pragma once

#include "lib/memory.hpp"

class Char {
private:
    char value;

public:
    /**
     * @brief Construct char from ASCII value
     */
    Char(char c);
    
    /**
     * @brief Construct char from integer
     */
    Char(int c);
    
    /**
     * @brief Get character value
     */
    char getValue() const;
    
    /**
     * @brief Check if character is digit
     */
    bool isDigit() const;
    
    /**
     * @brief Check if character is letter
     */
    bool isLetter() const;
    
    /**
     * @brief Check if character is whitespace
     */
    bool isWhitespace() const;
    
    /**
     * @brief Check if character is uppercase
     */
    bool isUpperCase() const;
    
    /**
     * @brief Check if character is lowercase
     */
    bool isLowerCase() const;
    
    /**
     * @brief Convert to uppercase
     */
    Char toUpperCase() const;
    
    /**
     * @brief Convert to lowercase
     */
    Char toLowerCase() const;
    
    /**
     * @brief Check equality
     */
    bool equals(const Char& other) const;
    
    /**
     * @brief Compare with another character
     */
    int compare(const Char& other) const;
    
    /**
     * @brief Convert to string (caller manages memory)
     */
    char* toString() const;
    
    /**
     * @brief Get ASCII value as integer
     */
    int toInt() const;
    
    /**
     * @brief Create from integer ASCII value
     */
    static Char fromInt(int ascii_value);
    
    /**
     * @brief Create newline character
     */
    static Char newline();
    
    /**
     * @brief Create tab character
     */
    static Char tab();
    
    /**
     * @brief Create space character
     */
    static Char space();
    
    /**
     * @brief Create null character
     */
    static Char null();
};