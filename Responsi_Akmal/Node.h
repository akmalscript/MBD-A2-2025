#pragma once
#include <vector>
#include <string>

enum class NodeType { 
    NODE_ROOT, 
    NODE_INTERNAL, 
    NODE_LEAF 
};

template <typename T>
class Node {
private:
    // Split operations
    Node<T>* splitLeaf(int rIndex);
    Node<T>* splitInternal(int rIndex);

public:
    // Node properties
    NodeType type;  // tipe node: root, internal, atau leaf
                    // type root adalah node yang tidak memiliki parent
                    // type internal adalah node yang memiliki parent dan memiliki children
                    // type leaf adalah node yang memiliki parent dan tidak memiliki children
    Node<T>* parent;
    int size;
    std::vector<int> keys;
    
    // For internal nodes
    std::vector<Node<T>*> children;
    
    // For leaf nodes
    std::vector<T> vals;
    Node<T>* prev;
    Node<T>* next;

    // Constructor and destructor
    Node();
    ~Node();

    // Key operations
    int findKey(int key);
    int keyInsertIndex(int key);
    int indexOfChild(Node<T>* child);

    // Remove operations
    void removeFromLeaf(int key);
    void removeFromInternal(int key);

    // Borrowing operations for leaf nodes
    void borrowFromRightLeaf();
    void borrowFromLeftLeaf();

    // Merging operations for leaf nodes
    void mergeWithRightLeaf();
    void mergeWithLeftLeaf();

    // Borrowing operations for internal nodes
    void borrowFromRightInternal(Node<T>* next);
    void borrowFromLeftInternal(Node<T>* prev);

    // Merging operations for internal nodes
    void mergeWithRightInternal(Node<T>* next);
    void mergeWithLeftInternal(Node<T>* prev);

    // Data operations
    void set(int key, const T& val);
    Node<T>* splitNode();
};
