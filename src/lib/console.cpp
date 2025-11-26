#include "console.hpp"
#include "../types/Number.hpp"
#include "../types/Boolean.hpp"
#include "../types/Char.hpp"
#include "../types/Strings.hpp"  // Add this include
#include "memory.hpp"
#include <stdio.h>

namespace Luna {
namespace Console {

void log(const char* message) {
    printf("\033[0m%s\033[0m\n", message); // Reset colors, print, reset again
}

void warn(const char* message) {
    printf("\033[43m\033[37m[WARN] %s\033[0m\n", message); // Yellow bg, white text
}

void error(const char* message) {
    printf("\033[41m\033[37m[ERROR] %s\033[0m\n", message); // Red bg, white text
}

void table(Array* data, Array* headers) {
    if (!data || data->isEmpty()) {
        warn("Table data is empty");
        return;
    }

    // Calculate column widths
    Array* colWidths = new Array();
    
    // If headers provided, use them for width calculation
    if (headers && !headers->isEmpty()) {
        for (size_t i = 0; i < headers->getLength(); i++) {
            char* headerStr = valueToString(headers->get(i));
            size_t width = Luna::string::length(headerStr);  // Use string::length
            colWidths->push(new Number((int32_t)(width + 2))); // +2 for padding
            if (headerStr) Memory::deallocate(headerStr);
        }
    }
    
    // Calculate max widths from data
    for (size_t row = 0; row < data->getLength(); row++) {
        Array* rowData = (Array*)data->get(row);
        if (!rowData) continue;
        
        for (size_t col = 0; col < rowData->getLength(); col++) {
            char* cellStr = valueToString(rowData->get(col));
            size_t width = Luna::string::length(cellStr);  // Use string::length
            
            if (col >= colWidths->getLength()) {
                colWidths->push(new Number((int32_t)(width + 2)));
            } else {
                Number* currentWidth = (Number*)colWidths->get(col);
                if (width + 2 > (size_t)currentWidth->toInt()) {
                    colWidths->set(col, new Number((int32_t)(width + 2)));
                    delete currentWidth;
                }
            }
            if (cellStr) Memory::deallocate(cellStr);
        }
    }

    // Print table border
    printf("┌");
    for (size_t i = 0; i < colWidths->getLength(); i++) {
        Number* width = (Number*)colWidths->get(i);
        for (int j = 0; j < width->toInt(); j++) {
            printf("─");
        }
        if (i < colWidths->getLength() - 1) printf("┬");
    }
    printf("┐\n");

    // Print headers if provided
    if (headers && !headers->isEmpty()) {
        printf("│");
        for (size_t i = 0; i < headers->getLength(); i++) {
            if (i < colWidths->getLength()) {
                char* headerStr = valueToString(headers->get(i));
                Number* width = (Number*)colWidths->get(i);
                printf(" %s", headerStr ? headerStr : "NULL");
                
                // Padding
                size_t currentLen = Luna::string::length(headerStr);  // Use string::length
                for (size_t j = currentLen + 1; j < (size_t)width->toInt(); j++) {
                    printf(" ");
                }
                printf("│");
                if (headerStr) Memory::deallocate(headerStr);
            }
        }
        printf("\n");

        // Print separator
        printf("├");
        for (size_t i = 0; i < colWidths->getLength(); i++) {
            Number* width = (Number*)colWidths->get(i);
            for (int j = 0; j < width->toInt(); j++) {
                printf("─");
            }
            if (i < colWidths->getLength() - 1) printf("┼");
        }
        printf("┤\n");
    }

    // Print data rows
    for (size_t row = 0; row < data->getLength(); row++) {
        printf("│");
        Array* rowData = (Array*)data->get(row);
        if (rowData) {
            for (size_t col = 0; col < rowData->getLength(); col++) {
                if (col < colWidths->getLength()) {
                    char* cellStr = valueToString(rowData->get(col));
                    Number* width = (Number*)colWidths->get(col);
                    printf(" %s", cellStr ? cellStr : "NULL");
                    
                    // Padding
                    size_t currentLen = Luna::string::length(cellStr);  // Use string::length
                    for (size_t j = currentLen + 1; j < (size_t)width->toInt(); j++) {
                        printf(" ");
                    }
                    printf("│");
                    if (cellStr) Memory::deallocate(cellStr);
                }
            }
        }
        printf("\n");
    }

    // Print bottom border
    printf("└");
    for (size_t i = 0; i < colWidths->getLength(); i++) {
        Number* width = (Number*)colWidths->get(i);
        for (int j = 0; j < width->toInt(); j++) {
            printf("─");
        }
        if (i < colWidths->getLength() - 1) printf("┴");
    }
    printf("┘\n");

    // Cleanup
    for (size_t i = 0; i < colWidths->getLength(); i++) {
        delete (Number*)colWidths->get(i);
    }
    delete colWidths;
}

void logMultiple(Array* args) {
    if (!args || args->isEmpty()) {
        log("");
        return;
    }

    for (size_t i = 0; i < args->getLength(); i++) {
        char* str = valueToString(args->get(i));
        if (i > 0) printf(" ");
        printf("%s", str ? str : "NULL");
        if (str) Memory::deallocate(str);
    }
    printf("\n");
}

char* valueToString(void* value) {
    if (!value) {
        char* nullStr = (char*)Memory::allocate(5);
        nullStr[0] = 'N'; nullStr[1] = 'U'; nullStr[2] = 'L'; nullStr[3] = 'L'; nullStr[4] = '\0';
        return nullStr;
    }

    // Without RTTI, we use a heuristic approach
    // We'll try each type and validate the result
    
    // Try Boolean first (smallest, most constrained)
    Boolean* boolVal = reinterpret_cast<Boolean*>(value);
    char* boolStr = boolVal->toString();
    if (boolStr) {
        // Check if it's a valid boolean string
        bool isTrue = (boolStr[0] == 'T' && boolStr[1] == 'r' && boolStr[2] == 'u' && boolStr[3] == 'e' && boolStr[4] == '\0');
        bool isFalse = (boolStr[0] == 'F' && boolStr[1] == 'a' && boolStr[2] == 'l' && boolStr[3] == 's' && boolStr[4] == 'e' && boolStr[5] == '\0');
        if (isTrue || isFalse) {
            return boolStr;
        }
        Memory::deallocate(boolStr);
    }
    
    // Try Char (also small and constrained)
    Char* charVal = reinterpret_cast<Char*>(value);
    char* charStr = charVal->toString();
    if (charStr) {
        // Char toString always returns a 2-character string (char + null)
        if (charStr[0] != '\0' && charStr[1] == '\0') {
            // Valid single character string
            return charStr;
        }
        Memory::deallocate(charStr);
    }
    
    // Try Number
    Number* num = reinterpret_cast<Number*>(value);
    char* numStr = num->toString();
    if (numStr) {
        // Number strings are digits, negative sign, or special values
        bool validNumber = false;
        if (numStr[0] == 'N' && numStr[1] == 'a' && numStr[2] == 'N' && numStr[3] == '\0') {
            validNumber = true; // NaN
        } else if (numStr[0] == 'I' || (numStr[0] == '-' && numStr[1] == 'I')) {
            validNumber = true; // Infinity or -Infinity
        } else if (numStr[0] == '-' || (numStr[0] >= '0' && numStr[0] <= '9')) {
            validNumber = true; // Regular number
        }
        
        if (validNumber) {
            return numStr;
        }
        Memory::deallocate(numStr);
    }

    // Try Array (check if getLength works reasonably)
    Array* arrayVal = reinterpret_cast<Array*>(value);
    size_t len = arrayVal->getLength();
    if (len < 10000) { // Sanity check - arrays shouldn't be huge in our tests
        char* arrayStr = (char*)Memory::allocate(32);
        arrayStr[0] = '[';
        size_t pos = 1;
        
        for (size_t i = 0; i < len && i < 3 && pos < 30; i++) {
            if (i > 0) {
                arrayStr[pos++] = ',';
                arrayStr[pos++] = ' ';
            }
            
            char* elementStr = valueToString(arrayVal->get(i));
            if (elementStr) {
                size_t j = 0;
                while (elementStr[j] != '\0' && pos < 28) {
                    arrayStr[pos++] = elementStr[j++];
                }
                Memory::deallocate(elementStr);
            }
        }
        
        if (len > 3) {
            arrayStr[pos++] = '.';
            arrayStr[pos++] = '.';
            arrayStr[pos++] = '.';
        }
        
        arrayStr[pos++] = ']';
        arrayStr[pos] = '\0';
        return arrayStr;
    }

    // Fallback: pointer address
    char* fallback = (char*)Memory::allocate(20);
    snprintf(fallback, 19, "[object %p]", value);
    return fallback;
}

} // namespace Console
} // namespace Luna