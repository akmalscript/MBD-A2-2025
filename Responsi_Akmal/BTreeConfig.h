#pragma once

namespace BTreeConfig {
    // Default minimum degree for B-tree
    constexpr int DEFAULT_DEGREE = 6;
    
    // Debug mode flag
    #ifdef DEBUG
        constexpr bool DEBUG_MODE = true;
    #else
        constexpr bool DEBUG_MODE = false;
    #endif
    
    // Memory management options
    constexpr bool USE_MEMORY_POOL = false;  // Future enhancement
    constexpr bool ENABLE_STATISTICS = false;  // Future enhancement
    
    // Tree visualization options
    constexpr const char* TREE_PREFIX_LAST = "   ";
    constexpr const char* TREE_PREFIX_CONT = "╎  ";
    constexpr const char* TREE_NODE_SYMBOL = "├ ";
    
    // Performance tuning
    constexpr int VECTOR_RESERVE_SIZE = 16;  // Initial capacity for vectors
    constexpr bool SHRINK_VECTORS = true;    // Whether to shrink vectors after operations
    
    // Validation options
    constexpr bool ENABLE_TREE_VALIDATION = DEBUG_MODE;
    constexpr bool STRICT_ERROR_CHECKING = DEBUG_MODE;
}

// Macro for debug output
#if BTreeConfig::DEBUG_MODE
    #include <iostream>
    #define BTREE_DEBUG(x) std::cout << "[DEBUG] " << x << std::endl
#else
    #define BTREE_DEBUG(x)
#endif

// Exception classes for better error handling
#include <stdexcept>

namespace BTreeExceptions {
    class InvalidDegree : public std::invalid_argument {
    public:
        InvalidDegree(int degree) 
            : std::invalid_argument("Invalid B-tree degree: " + std::to_string(degree)) {}
    };
    
    class KeyNotFound : public std::runtime_error {
    public:
        KeyNotFound(int key) 
            : std::runtime_error("Key not found: " + std::to_string(key)) {}
    };
    
    class TreeCorrupted : public std::runtime_error {
    public:
        TreeCorrupted(const std::string& message) 
            : std::runtime_error("Tree corruption detected: " + message) {}
    };
}
