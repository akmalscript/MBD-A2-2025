#pragma once
#include "Node.h"
#include <string>

template <typename T>
class BTree {
private:
    Node<T>* findLeaf(int key);
    void remove(int key, Node<T>* curr);
    void printTree(Node<T>* node, const std::string& prefix, bool last);

public:
    int deg;
    // deg adalah derajat dari B-Tree, yaitu jumlah maksimum anak yang dimiliki oleh setiap node internal
    // dan jumlah maksimum kunci yang dimiliki oleh setiap node internal
    // dan jumlah maksimum kunci yang dimiliki oleh setiap node leaf
    int depth;
    // depth adalah kedalaman dari B-Tree, yaitu jumlah maksimum level yang dimiliki oleh B-Tree
    // kedalaman B-Tree adalah jumlah maksimum level yang dimiliki oleh B-Tree
    Node<T>* root;

    // Constructor and destructor
    explicit BTree(int degree);
    ~BTree();

    // Public interface
    void set(int key, const T& val);
    void remove(int key);
    T* find(int key);
    
    // Utility functions
    void printTree();
    bool empty() const;
    void clear();
};
