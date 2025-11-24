#pragma once

#include "lib/memory.hpp"

class Array {
private:
    void** data;
    size_t capacity;
    size_t length;

public:
    /**
     * @brief Construct empty array
     */
    Array();
    
    /**
     * @brief Construct array with initial capacity
     */
    Array(size_t initial_capacity);
    
    /**
     * @brief Destroy array and free memory
     */
    ~Array();
    
    /**
     * @brief Get element at index
     */
    void* get(size_t index) const;
    
    /**
     * @brief Set element at index
     */
    void set(size_t index, void* value);
    
    /**
     * @brief Append element to end
     */
    void push(void* value);
    
    /**
     * @brief Remove and return last element
     */
    void* pop();
    
    /**
     * @brief Insert element at index
     */
    void insert(size_t index, void* value);
    
    /**
     * @brief Remove element at index
     */
    void* remove(size_t index);
    
    /**
     * @brief Get array length
     */
    size_t getLength() const;
    
    /**
     * @brief Get array capacity
     */
    size_t getCapacity() const;
    
    /**
     * @brief Check if array is empty
     */
    bool isEmpty() const;
    
    /**
     * @brief Clear all elements
     */
    void clear();
    
    /**
     * @brief Find index of element
     */
    int indexOf(void* value) const;
    
    /**
     * @brief Check if array contains element
     */
    bool contains(void* value) const;

private:
    /**
     * @brief Resize array if needed
     */
    void resizeIfNeeded();
};