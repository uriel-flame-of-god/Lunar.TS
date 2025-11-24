#pragma once

typedef unsigned char uint8_t;

class Boolean {
private:
    uint8_t value;

public:
    /**
     * @brief Construct boolean value
     */
    Boolean(bool value);
    
    /**
     * @brief Logical AND operation
     */
    Boolean logicalAnd(const Boolean& other) const;
    
    /**
     * @brief Logical OR operation
     */
    Boolean logicalOr(const Boolean& other) const;
    
    /**
     * @brief Logical NOT operation
     */
    Boolean logicalNot() const;
    
    /**
     * @brief Check equality
     */
    bool equals(const Boolean& other) const;
    
    /**
     * @brief Convert to string (caller manages memory)
     */
    char* toString() const;
    
    /**
     * @brief Get boolean value
     */
    bool getValue() const;
    
    /**
     * @brief Create true value
     */
    static Boolean trueValue();
    
    /**
     * @brief Create false value
     */
    static Boolean falseValue();
};
