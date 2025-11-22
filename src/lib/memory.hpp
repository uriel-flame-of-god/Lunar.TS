#pragma once

#ifdef LUNA_USE_STDLIB
#include <cstddef>
#else
typedef unsigned long size_t;
typedef unsigned long uintptr_t;
#endif

namespace Luna {
namespace Memory {

/**
 * @brief Allocate memory of specified size
 * @param size - Number of bytes to allocate
 * @returns Pointer to allocated memory or nullptr
 */
void* allocate(size_t size);

/**
 * @brief Deallocate memory at pointer
 * @param ptr - Pointer to deallocate
 */
void deallocate(void* ptr);

/**
 * @brief Reallocate memory to new size
 * @param ptr - Existing pointer (or nullptr)
 * @param new_size - New size in bytes
 * @returns Pointer to reallocated memory
 */
void* reallocate(void* ptr, size_t new_size);

/**
 * @brief Copy memory from src to dest
 * @param dest - Destination pointer
 * @param src - Source pointer
 * @param n - Number of bytes to copy
 */
void copy(void* dest, const void* src, size_t n);

/**
 * @brief Set memory to value
 * @param dest - Destination pointer
 * @param value - Value to set
 * @param n - Number of bytes
 */
void set(void* dest, int value, size_t n);

/**
 * @brief Compare memory regions
 * @param ptr1 - First pointer
 * @param ptr2 - Second pointer
 * @param n - Number of bytes to compare
 * @returns 0 if equal, -1 if ptr1<ptr2, 1 if ptr1>ptr2
 */
int compare(const void* ptr1, const void* ptr2, size_t n);

/**
 * @brief Check if stdlib is available
 * @returns true if LUNA_USE_STDLIB is defined
 */
bool has_stdlib();

/**
 * @brief Initialize memory system
 */
void initialize();

/**
 * @brief Shutdown memory system
 */
void shutdown();

} // namespace Memory
} // namespace Luna