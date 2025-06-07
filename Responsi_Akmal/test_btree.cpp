#include "BTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <random>
#include <algorithm>

class BTreeTester {
private:
    int tests_passed = 0;
    int tests_failed = 0;

    void assert_test(bool condition, const std::string& test_name) {
        if (condition) {
            std::cout << "✓ " << test_name << " PASSED" << std::endl;
            tests_passed++;
        } else {
            std::cout << "✗ " << test_name << " FAILED" << std::endl;
            tests_failed++;
        }
    }

public:
    void test_basic_operations() {
        std::cout << "\n=== Testing Basic Operations ===" << std::endl;
        
        BTree<std::string> btree(4);
        
        // Test empty tree
        assert_test(btree.empty(), "Empty tree check");
        assert_test(btree.find(1) == nullptr, "Find in empty tree");
        
        // Test single insertion
        btree.set(5, "five");
        assert_test(!btree.empty(), "Tree not empty after insertion");
        
        std::string* result = btree.find(5);
        assert_test(result != nullptr && *result == "five", "Find single element");
        
        // Test multiple insertions
        btree.set(3, "three");
        btree.set(7, "seven");
        btree.set(1, "one");
        btree.set(9, "nine");
        
        assert_test(btree.find(3) != nullptr && *btree.find(3) == "three", "Find after multiple insertions");
        assert_test(btree.find(10) == nullptr, "Find non-existent key");
    }

    void test_overwrite_values() {
        std::cout << "\n=== Testing Value Overwriting ===" << std::endl;
        
        BTree<std::string> btree(4);
        
        btree.set(5, "five");
        btree.set(5, "FIVE");  // Overwrite
        
        std::string* result = btree.find(5);
        assert_test(result != nullptr && *result == "FIVE", "Value overwrite");
    }

    void test_deletion_operations() {
        std::cout << "\n=== Testing Deletion Operations ===" << std::endl;
        
        BTree<std::string> btree(4);
        
        // Insert test data
        std::vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        for (int key : keys) {
            btree.set(key, "value_" + std::to_string(key));
        }
        
        // Test deletion
        btree.remove(5);
        assert_test(btree.find(5) == nullptr, "Key deleted successfully");
        assert_test(btree.find(4) != nullptr, "Adjacent key still exists");
        
        // Test multiple deletions
        btree.remove(1);
        btree.remove(10);
        btree.remove(3);
        
        assert_test(btree.find(1) == nullptr, "Multiple deletions - key 1");
        assert_test(btree.find(10) == nullptr, "Multiple deletions - key 10");
        assert_test(btree.find(3) == nullptr, "Multiple deletions - key 3");
        assert_test(btree.find(2) != nullptr, "Remaining key still accessible");
    }

    void test_large_dataset() {
        std::cout << "\n=== Testing Large Dataset ===" << std::endl;
        
        BTree<int> btree(6);
        const int num_elements = 1000;
        
        // Insert many elements
        for (int i = 1; i <= num_elements; i++) {
            btree.set(i, i * 10);
        }
        
        // Verify all elements
        bool all_found = true;
        for (int i = 1; i <= num_elements; i++) {
            int* result = btree.find(i);
            if (!result || *result != i * 10) {
                all_found = false;
                break;
            }
        }
        assert_test(all_found, "Large dataset insertion and retrieval");
        
        // Remove half the elements
        for (int i = 1; i <= num_elements; i += 2) {
            btree.remove(i);
        }
        
        // Verify removals
        bool removals_correct = true;
        for (int i = 1; i <= num_elements; i++) {
            int* result = btree.find(i);
            if (i % 2 == 1) {  // Should be removed
                if (result != nullptr) {
                    removals_correct = false;
                    break;
                }
            } else {  // Should still exist
                if (!result || *result != i * 10) {
                    removals_correct = false;
                    break;
                }
            }
        }
        assert_test(removals_correct, "Large dataset partial removal");
    }

    void test_random_operations() {
        std::cout << "\n=== Testing Random Operations ===" << std::endl;
        
        BTree<std::string> btree(5);
        std::vector<int> inserted_keys;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        
        // Random insertions
        for (int i = 0; i < 50; i++) {
            int key = dis(gen);
            std::string value = "val_" + std::to_string(key);
            btree.set(key, value);
            
            if (std::find(inserted_keys.begin(), inserted_keys.end(), key) == inserted_keys.end()) {
                inserted_keys.push_back(key);
            }
        }
        
        // Verify all inserted keys can be found
        bool all_random_found = true;
        for (int key : inserted_keys) {
            std::string* result = btree.find(key);
            if (!result || *result != "val_" + std::to_string(key)) {
                all_random_found = false;
                break;
            }
        }
        assert_test(all_random_found, "Random insertions verification");
        
        // Random deletions
        std::shuffle(inserted_keys.begin(), inserted_keys.end(), gen);
        int to_delete = inserted_keys.size() / 2;
        
        for (int i = 0; i < to_delete; i++) {
            btree.remove(inserted_keys[i]);
            inserted_keys[i] = -1;  // Mark as deleted
        }
        
        // Verify deletions
        bool random_deletions_correct = true;
        for (int key : inserted_keys) {
            std::string* result = btree.find(key);
            if (key == -1) {  // Skip deleted markers
                continue;
            }
            
            if (!result || *result != "val_" + std::to_string(key)) {
                random_deletions_correct = false;
                break;
            }
        }
        assert_test(random_deletions_correct, "Random deletions verification");
    }

    void test_different_degrees() {
        std::cout << "\n=== Testing Different Tree Degrees ===" << std::endl;
        
        std::vector<int> degrees = {3, 4, 5, 6, 10, 20};
        bool all_degrees_work = true;
        
        for (int degree : degrees) {
            BTree<int> btree(degree);
            
            // Insert test data
            for (int i = 1; i <= 20; i++) {
                btree.set(i, i * i);
            }
            
            // Verify data
            for (int i = 1; i <= 20; i++) {
                int* result = btree.find(i);
                if (!result || *result != i * i) {
                    all_degrees_work = false;
                    break;
                }
            }
            
            if (!all_degrees_work) break;
        }
        
        assert_test(all_degrees_work, "Multiple tree degrees");
    }

    void test_edge_cases() {
        std::cout << "\n=== Testing Edge Cases ===" << std::endl;
        
        BTree<std::string> btree(3);
        
        // Test removing from empty tree
        btree.remove(999);  // Should not crash
        assert_test(true, "Remove from empty tree (no crash)");
        
        // Test duplicate removals
        btree.set(5, "five");
        btree.remove(5);
        btree.remove(5);  // Remove again
        assert_test(btree.find(5) == nullptr, "Duplicate removal handling");
        
        // Test with minimum degree
        BTree<int> min_btree(2);  // Very small degree
        for (int i = 1; i <= 10; i++) {
            min_btree.set(i, i);
        }
        
        bool min_degree_works = true;
        for (int i = 1; i <= 10; i++) {
            int* result = min_btree.find(i);
            if (!result || *result != i) {
                min_degree_works = false;
                break;
            }
        }
        assert_test(min_degree_works, "Minimum degree tree operations");
    }

    void run_all_tests() {
        std::cout << "Starting B-Tree Comprehensive Tests\n";
        std::cout << "====================================" << std::endl;
        
        test_basic_operations();
        test_overwrite_values();
        test_large_dataset();
        test_random_operations();
        test_different_degrees();
        test_edge_cases();
        test_deletion_operations();
        
        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Tests Passed: " << tests_passed << std::endl;
        std::cout << "Tests Failed: " << tests_failed << std::endl;
        std::cout << "Total Tests:  " << (tests_passed + tests_failed) << std::endl;
        
        if (tests_failed == 0) {
            std::cout << "\n🎉 All tests passed! B-Tree implementation is working correctly." << std::endl;
        } else {
            std::cout << "\n❌ Some tests failed. Please review the implementation." << std::endl;
        }
    }
};

int main() {
    BTreeTester tester;
    tester.run_all_tests();
    return 0;
}
