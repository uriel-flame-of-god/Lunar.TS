#pragma once

#include "types/Array.hpp"
#include "lib/memory.hpp"

namespace Luna {

// ===== C-STYLE STRING FUNCTIONS (replaces string.h) =====
namespace string {
    /**
     * @brief Get length of C-string
     */
    size_t length(const char* str);
    
    /**
     * @brief Compare two C-strings
     * @returns 0 if equal, <0 if s1<s2, >0 if s1>s2
     */
    int compare(const char* s1, const char* s2);
    
    /**
     * @brief Copy C-string with length limit
     */
    char* copy(char* dest, const char* src, size_t n);
    
    /**
     * @brief Duplicate C-string (caller manages memory)
     */
    char* duplicate(const char* str);
    
    /**
     * @brief Free duplicated string
     */
    void free(char* str);
    
    /**
     * @brief Find character in string
     */
    const char* find(const char* str, char ch);
    
    /**
     * @brief Concatenate two C-strings (caller manages memory)
     */
    char* concatenate(const char* str1, const char* str2);
    
    /**
     * @brief Convert integer to string (caller manages memory)
     */
    char* fromInt(int value);
    
    /**
     * @brief Convert double to string (caller manages memory)
     */
    char* fromDouble(double value);
}

// ===== TYPESCRIPT STRING TYPE =====
namespace std {
    // For substring operations
    static const size_t npos = -1;
    
    class string {
    private:
        char* data_;
        size_t length_;
        size_t capacity_;
        
        /**
         * @brief Resize internal buffer
         */
        void resize(size_t new_capacity);
        
    public:
        // ===== CONSTRUCTORS/DESTRUCTOR =====
        string();
        string(const char* cstr);
        string(const string& other);
        string(char ch);
        ~string();
        
        // ===== CAPACITY =====
        size_t length() const { return length_; }
        size_t size() const { return length_; }
        bool empty() const { return length_ == 0; }
        void clear();
        
        // ===== ELEMENT ACCESS =====
        const char* c_str() const { return data_ ? data_ : ""; }
        char& operator[](size_t pos);
        const char& operator[](size_t pos) const;
        char at(size_t pos) const;
        
        // ===== MODIFICATION =====
        string& operator=(const string& other);
        string& operator=(const char* cstr);
        string& operator+=(const string& other);
        string& operator+=(const char* cstr);
        string& operator+=(char ch);
        
        void push_back(char ch);
        void append(const string& other);
        void append(const char* cstr);
        
        // ===== TYPESCRIPT-SPECIFIC METHODS =====
        string substr(size_t pos, size_t len = npos) const;
        size_t find(const string& str, size_t pos = 0) const;
        size_t find(char ch, size_t pos = 0) const;
        
        string toUpperCase() const;
        string toLowerCase() const;
        string trim() const;
        
        bool startsWith(const string& prefix) const;
        bool endsWith(const string& suffix) const;
        bool includes(const string& search) const;
        
        Array* split(const string& delimiter) const;
        string replace(const string& search, const string& replacement) const;
        
        // ===== CONVERSION =====
        int toInt() const;
        double toDouble() const;
        bool toBoolean() const;
        
        // ===== ITERATION =====
        class iterator {
        private:
            char* ptr_;
        public:
            iterator(char* ptr) : ptr_(ptr) {}
            char& operator*() { return *ptr_; }
            iterator& operator++() { ++ptr_; return *this; }
            bool operator!=(const iterator& other) { return ptr_ != other.ptr_; }
        };
        
        iterator begin() { return iterator(data_); }
        iterator end() { return iterator(data_ + length_); }
    };
    
    // ===== NON-MEMBER OPERATORS =====
    string operator+(const string& lhs, const string& rhs);
    string operator+(const string& lhs, const char* rhs);
    string operator+(const char* lhs, const string& rhs);
    
    bool operator==(const string& lhs, const string& rhs);
    bool operator==(const string& lhs, const char* rhs);
    bool operator==(const char* lhs, const string& rhs);
    
    bool operator!=(const string& lhs, const string& rhs);
    bool operator!=(const string& lhs, const char* rhs);
    bool operator!=(const char* lhs, const string& rhs);
    
    bool operator<(const string& lhs, const string& rhs);
    bool operator>(const string& lhs, const string& rhs);
    bool operator<=(const string& lhs, const string& rhs);
    bool operator>=(const string& lhs, const string& rhs);
}

} // namespace Luna