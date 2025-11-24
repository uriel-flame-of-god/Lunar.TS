#pragma once

#include "../types/Array.hpp"

namespace Luna {
namespace Console {

/**
 * @brief Log levels for console output
 */
enum class LogLevel {
    LOG,
    WARN,
    ERROR
};

/**
 * @brief Basic log function
 * @param message - String message to log
 */
void log(const char* message);

/**
 * @brief Log with warning styling (yellow background, white text)
 * @param message - String message to log as warning
 */
void warn(const char* message);

/**
 * @brief Log with error styling (red background, white text)
 * @param message - String message to log as error
 */
void error(const char* message);

/**
 * @brief Display data in table format
 * @param data - 2D array of data to display
 * @param headers - Optional array of column headers
 */
void table(Array* data, Array* headers = nullptr);

/**
 * @brief Log multiple values
 * @param args - Array of values to log
 */
void logMultiple(Array* args);

/**
 * @brief Convert any value to string for logging
 * @param value - Pointer to any value
 * @returns String representation (caller manages memory)
 */
char* valueToString(void* value);

} // namespace Console
} // namespace Luna