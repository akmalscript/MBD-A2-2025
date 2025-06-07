#include "BTree.h"
#include <iostream>
#include <string>

int main() {
    // Create a B-tree with degree 6
    BTree<std::string> btree(6);
    
    std::cout << "Inserting values into B-tree...\n";
    
    // Insert key-value pairs
    btree.set(1, "one");
    btree.set(2, "two");
    btree.set(3, "three");
    btree.set(4, "four");
    btree.set(5, "five");
    btree.set(6, "six");
    btree.set(7, "seven");
    btree.set(9, "nine");
    btree.set(11, "eleven");
    btree.set(8, "eight");
    btree.set(10, "ten");

    std::cout << "\nB-tree structure after insertions:\n";
    btree.printTree();

    // Test find operation
    std::cout << "\nTesting find operations:\n";
    std::string* result = btree.find(5);
    if (result) {
        std::cout << "Key 5: " << *result << std::endl;
    } else {
        std::cout << "Key 5 not found" << std::endl;
    }

    result = btree.find(15);
    if (result) {
        std::cout << "Key 15: " << *result << std::endl;
    } else {
        std::cout << "Key 15 not found" << std::endl;
    }

    std::cout << "\nRemoving keys: 1, 5, 3, 8\n";
    
    // Remove some keys
    btree.remove(1);
    btree.remove(5);
    btree.remove(3);
    btree.remove(8);

    std::cout << "\nB-tree structure after removals:\n";
    btree.printTree();

    return 0;
}
