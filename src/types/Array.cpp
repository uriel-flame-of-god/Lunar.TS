#include "Array.hpp"
#include "lib/memory.hpp"

Array::Array() : capacity(8), length(0) {
    data = (void**)Luna::Memory::allocate(capacity * sizeof(void*));
    Luna::Memory::set(data, 0, capacity * sizeof(void*));
}

Array::Array(size_t initial_capacity) : capacity(initial_capacity), length(0) {
    if (capacity < 1) capacity = 1;
    data = (void**)Luna::Memory::allocate(capacity * sizeof(void*));
    Luna::Memory::set(data, 0, capacity * sizeof(void*));
}

Array::~Array() {
    if (data) {
        Luna::Memory::deallocate(data);
    }
}

void* Array::get(size_t index) const {
    if (index >= length) return nullptr;
    return data[index];
}

void Array::set(size_t index, void* value) {
    if (index >= length) return;
    data[index] = value;
}

void Array::push(void* value) {
    resizeIfNeeded();
    data[length++] = value;
}

void* Array::pop() {
    if (length == 0) return nullptr;
    return data[--length];
}

void Array::insert(size_t index, void* value) {
    if (index > length) return;
    
    resizeIfNeeded();
    
    // Shift elements to the right
    for (size_t i = length; i > index; i--) {
        data[i] = data[i - 1];
    }
    
    data[index] = value;
    length++;
}

void* Array::remove(size_t index) {
    if (index >= length) return nullptr;
    
    void* removed = data[index];
    
    // Shift elements to the left
    for (size_t i = index; i < length - 1; i++) {
        data[i] = data[i + 1];
    }
    
    length--;
    data[length] = nullptr; // Clear last element
    
    return removed;
}

size_t Array::getLength() const {
    return length;
}

size_t Array::getCapacity() const {
    return capacity;
}

bool Array::isEmpty() const {
    return length == 0;
}

void Array::clear() {
    length = 0;
    // Optional: zero out the array
    Luna::Memory::set(data, 0, capacity * sizeof(void*));
}

int Array::indexOf(void* value) const {
    for (size_t i = 0; i < length; i++) {
        if (data[i] == value) {
            return (int)i;
        }
    }
    return -1;
}

bool Array::contains(void* value) const {
    return indexOf(value) != -1;
}

void Array::resizeIfNeeded() {
    if (length < capacity) return;
    
    size_t new_capacity = capacity * 2;
    void** new_data = (void**)Luna::Memory::allocate(new_capacity * sizeof(void*));
    
    // Copy existing data
    Luna::Memory::copy(new_data, data, length * sizeof(void*));
    
    // Zero out the rest
    Luna::Memory::set(new_data + length, 0, (new_capacity - length) * sizeof(void*));
    
    // Replace old data
    Luna::Memory::deallocate(data);
    data = new_data;
    capacity = new_capacity;
}