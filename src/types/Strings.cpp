#include "Strings.hpp"
#include "types/Number.hpp"
#include "types/Boolean.hpp"

namespace Luna {

// ===== C-STYLE STRING FUNCTIONS =====
namespace string {

size_t length(const char* str) {
    if (!str) return 0;
    size_t len = 0;
    while (str[len] != '\0') len++;
    return len;
}

int compare(const char* s1, const char* s2) {
    if (!s1 || !s2) {
        if (!s1 && !s2) return 0;
        return s1 ? 1 : -1;
    }
    
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char* copy(char* dest, const char* src, size_t n) {
    if (!dest || !src || n == 0) return dest;
    
    char* d = dest;
    const char* s = src;
    size_t i = 0;
    
    while (i < n && *s) {
        *d++ = *s++;
        i++;
    }
    
    // Null terminate if we have space
    if (i < n) {
        *d = '\0';
    }
    
    return dest;
}

char* duplicate(const char* str) {
    if (!str) return nullptr;
    
    size_t len = length(str);
    char* new_str = (char*)Memory::allocate(len + 1);
    if (new_str) {
        copy(new_str, str, len + 1);
    }
    return new_str;
}

void free(char* str) {
    if (str) {
        Memory::deallocate(str);
    }
}

const char* find(const char* str, char ch) {
    if (!str) return nullptr;
    
    while (*str) {
        if (*str == ch) return str;
        str++;
    }
    return nullptr;
}

char* concatenate(const char* str1, const char* str2) {
    if (!str1 && !str2) return nullptr;
    if (!str1) return duplicate(str2);
    if (!str2) return duplicate(str1);
    
    size_t len1 = length(str1);
    size_t len2 = length(str2);
    char* result = (char*)Memory::allocate(len1 + len2 + 1);
    
    if (result) {
        copy(result, str1, len1 + 1);
        copy(result + len1, str2, len2 + 1);
    }
    
    return result;
}

char* fromInt(int value) {
    // Simple implementation - can be optimized
    bool negative = value < 0;
    unsigned int abs_value = negative ? -value : value;
    
    // Count digits
    int digits = 1;
    unsigned int temp = abs_value;
    while (temp >= 10) {
        digits++;
        temp /= 10;
    }
    
    size_t total_len = digits + (negative ? 1 : 0);
    char* result = (char*)Memory::allocate(total_len + 1);
    
    if (result) {
        char* ptr = result + total_len;
        *ptr = '\0';
        
        do {
            *--ptr = '0' + (abs_value % 10);
            abs_value /= 10;
        } while (abs_value > 0);
        
        if (negative) {
            *--ptr = '-';
        }
    }
    
    return result;
}

char* fromDouble(double value) {
    // Simple implementation - can be enhanced
    if (value != value) return duplicate("NaN"); // NaN check
    
    // For now, just convert integer part
    return fromInt((int)value);
}

} // namespace string

// ===== TYPESCRIPT STRING TYPE =====  
namespace std {

// Private methods
void string::resize(size_t new_capacity) {
    if (new_capacity <= capacity_) return;
    
    char* new_data = (char*)Memory::allocate(new_capacity);
    if (new_data) {
        if (data_) {
            // Use Luna::string namespace for C-style functions
            Luna::string::copy(new_data, data_, length_ + 1);
            Memory::deallocate(data_);
        } else {
            new_data[0] = '\0';
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }
}

// Constructors/Destructor
string::string() : data_(nullptr), length_(0), capacity_(0) {
    resize(16); // Default initial capacity
}

string::string(const char* cstr) : data_(nullptr), length_(0), capacity_(0) {
    if (cstr) {
        // Use Luna::string namespace for C-style functions
        length_ = Luna::string::length(cstr);
        resize(length_ + 1);
        if (data_) {
            Luna::string::copy(data_, cstr, length_ + 1);
        }
    } else {
        resize(16);
    }
}

string::string(const string& other) : data_(nullptr), length_(0), capacity_(0) {
    length_ = other.length_;
    resize(length_ + 1);
    if (data_ && other.data_) {
        Luna::string::copy(data_, other.data_, length_ + 1);
    }
}

string::string(char ch) : data_(nullptr), length_(0), capacity_(0) {
    resize(2);
    if (data_) {
        data_[0] = ch;
        data_[1] = '\0';
        length_ = 1;
    }
}

string::~string() {
    if (data_) {
        Memory::deallocate(data_);
    }
}

// Capacity
void string::clear() {
    if (data_) {
        data_[0] = '\0';
    }
    length_ = 0;
}

// Element access
char& string::operator[](size_t pos) {
    return data_[pos];
}

const char& string::operator[](size_t pos) const {
    return data_[pos];
}

char string::at(size_t pos) const {
    if (pos >= length_) return '\0';
    return data_[pos];
}

// Modification
string& string::operator=(const string& other) {
    if (this != &other) {
        length_ = other.length_;
        resize(length_ + 1);
        if (data_ && other.data_) {
            Luna::string::copy(data_, other.data_, length_ + 1);
        }
    }
    return *this;
}

string& string::operator=(const char* cstr) {
    if (cstr) {
        // Use Luna::string namespace for C-style functions
        length_ = Luna::string::length(cstr);
        resize(length_ + 1);
        if (data_) {
            Luna::string::copy(data_, cstr, length_ + 1);
        }
    } else {
        clear();
    }
    return *this;
}

string& string::operator+=(const string& other) {
    append(other);
    return *this;
}

string& string::operator+=(const char* cstr) {
    append(cstr);
    return *this;
}

string& string::operator+=(char ch) {
    push_back(ch);
    return *this;
}

void string::push_back(char ch) {
    resize(length_ + 2); // +1 for char, +1 for null terminator
    if (data_) {
        data_[length_++] = ch;
        data_[length_] = '\0';
    }
}

void string::append(const string& other) {
    if (other.empty()) return;
    
    size_t new_length = length_ + other.length_;
    resize(new_length + 1);
    if (data_ && other.data_) {
        Luna::string::copy(data_ + length_, other.data_, other.length_ + 1);
        length_ = new_length;
    }
}

void string::append(const char* cstr) {
    if (!cstr) return;
    
    // Use Luna::string namespace for C-style functions
    size_t other_len = Luna::string::length(cstr);
    if (other_len == 0) return;
    
    size_t new_length = length_ + other_len;
    resize(new_length + 1);
    if (data_) {
        Luna::string::copy(data_ + length_, cstr, other_len + 1);
        length_ = new_length;
    }
}

// TypeScript-specific methods
string string::substr(size_t pos, size_t len) const {
    if (pos >= length_) return string();
    
    size_t actual_len = (len == npos || pos + len > length_) ? length_ - pos : len;
    string result;
    result.resize(actual_len + 1);
    
    for (size_t i = 0; i < actual_len; i++) {
        result.data_[i] = data_[pos + i];
    }
    result.data_[actual_len] = '\0';
    result.length_ = actual_len;
    
    return result;
}

size_t string::find(const string& str, size_t pos) const {
    if (str.empty() || pos >= length_) return npos;
    
    for (size_t i = pos; i <= length_ - str.length_; i++) {
        bool found = true;
        for (size_t j = 0; j < str.length_; j++) {
            if (data_[i + j] != str.data_[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    
    return npos;
}

size_t string::find(char ch, size_t pos) const {
    if (pos >= length_) return npos;
    
    for (size_t i = pos; i < length_; i++) {
        if (data_[i] == ch) return i;
    }
    
    return npos;
}

string string::toUpperCase() const {
    string result(*this);
    for (size_t i = 0; i < result.length_; i++) {
        char c = result.data_[i];
        if (c >= 'a' && c <= 'z') {
            result.data_[i] = c - 32;
        }
    }
    return result;
}

string string::toLowerCase() const {
    string result(*this);
    for (size_t i = 0; i < result.length_; i++) {
        char c = result.data_[i];
        if (c >= 'A' && c <= 'Z') {
            result.data_[i] = c + 32;
        }
    }
    return result;
}

string string::trim() const {
    if (empty()) return *this;
    
    size_t start = 0;
    size_t end = length_ - 1;
    
    // Find first non-whitespace
    while (start <= end && (data_[start] == ' ' || data_[start] == '\t' || data_[start] == '\n' || data_[start] == '\r')) {
        start++;
    }
    
    // Find last non-whitespace
    while (end >= start && (data_[end] == ' ' || data_[end] == '\t' || data_[end] == '\n' || data_[end] == '\r')) {
        end--;
    }
    
    if (start > end) return string(); // All whitespace
    
    return substr(start, end - start + 1);
}

bool string::startsWith(const string& prefix) const {
    if (prefix.length_ > length_) return false;
    
    for (size_t i = 0; i < prefix.length_; i++) {
        if (data_[i] != prefix.data_[i]) return false;
    }
    return true;
}

bool string::endsWith(const string& suffix) const {
    if (suffix.length_ > length_) return false;
    
    size_t start = length_ - suffix.length_;
    for (size_t i = 0; i < suffix.length_; i++) {
        if (data_[start + i] != suffix.data_[i]) return false;
    }
    return true;
}

bool string::includes(const string& search) const {
    return find(search) != npos;
}

Array* string::split(const string& delimiter) const {
    Array* result = new Array();
    if (delimiter.empty() || empty()) {
        result->push(new string(*this));
        return result;
    }
    
    size_t start = 0;
    size_t end = find(delimiter);
    
    while (end != npos) {
        result->push(new string(substr(start, end - start)));
        start = end + delimiter.length_;
        end = find(delimiter, start);
    }
    
    // Add the remaining part
    result->push(new string(substr(start)));
    
    return result;
}

string string::replace(const string& search, const string& replacement) const {
    if (search.empty()) return *this;
    
    string result;
    size_t start = 0;
    size_t end = find(search);
    
    while (end != npos) {
        result.append(substr(start, end - start));
        result.append(replacement);
        start = end + search.length_;
        end = find(search, start);
    }
    
    // Add the remaining part
    result.append(substr(start));
    
    return result;
}

// Conversion methods
int string::toInt() const {
    if (empty()) return 0;
    
    int result = 0;
    int sign = 1;
    size_t start = 0;
    
    // Handle sign
    if (data_[0] == '-') {
        sign = -1;
        start = 1;
    } else if (data_[0] == '+') {
        start = 1;
    }
    
    // Convert digits
    for (size_t i = start; i < length_; i++) {
        char c = data_[i];
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        } else {
            break; // Stop at first non-digit
        }
    }
    
    return result * sign;
}

double string::toDouble() const {
    // Simple implementation - convert to int for now
    return (double)toInt();
}

bool string::toBoolean() const {
    if (empty()) return false;
    
    // Check for "true" (case insensitive)
    if (length_ == 4) {
        return (data_[0] == 't' || data_[0] == 'T') &&
               (data_[1] == 'r' || data_[1] == 'R') &&
               (data_[2] == 'u' || data_[2] == 'U') &&
               (data_[3] == 'e' || data_[3] == 'E');
    }
    
    // Check for non-zero numbers
    int num = toInt();
    return num != 0;
}

// Non-member operators
string operator+(const string& lhs, const string& rhs) {
    string result(lhs);
    result.append(rhs);
    return result;
}

string operator+(const string& lhs, const char* rhs) {
    string result(lhs);
    result.append(rhs);
    return result;
}

string operator+(const char* lhs, const string& rhs) {
    string result(lhs);
    result.append(rhs);
    return result;
}

bool operator==(const string& lhs, const string& rhs) {
    // Use Luna::string namespace for C-style functions
    return Luna::string::compare(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator==(const string& lhs, const char* rhs) {
    return Luna::string::compare(lhs.c_str(), rhs) == 0;
}

bool operator==(const char* lhs, const string& rhs) {
    return Luna::string::compare(lhs, rhs.c_str()) == 0;
}

bool operator!=(const string& lhs, const string& rhs) {
    return !(lhs == rhs);
}

bool operator!=(const string& lhs, const char* rhs) {
    return !(lhs == rhs);
}

bool operator!=(const char* lhs, const string& rhs) {
    return !(lhs == rhs);
}

bool operator<(const string& lhs, const string& rhs) {
    return Luna::string::compare(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>(const string& lhs, const string& rhs) {
    return Luna::string::compare(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<=(const string& lhs, const string& rhs) {
    return Luna::string::compare(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const string& lhs, const string& rhs) {
    return Luna::string::compare(lhs.c_str(), rhs.c_str()) >= 0;
}

} // namespace std
} // namespace Luna