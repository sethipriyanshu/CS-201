/* 
Name: Priyanshu Sethi
Email: psethi@crimson.ua.edu
Course Section: Fall 2024 CS 201
Homework #: 2
*/

#ifndef _ST_HPP_
#include <utility>
#include <vector>
#include <iostream>
#define _ST_HPP_
#include "RBT.hpp"
#include "RBTPrint.hpp"

// Provides additional functionality like clear, insert, remove, and conversion to vector
template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
    typedef RBTNode<Key, Type>* iterator;

    // Default constructor
    ST() {}

    // Destructor, clears the tree to free memory
    ~ST() {
        clear();
    }

    // Overloads the [] operator for easy access and modification of nodes
    Type& operator[](const Key& key) {
        RBTNode<Key, Type>* node = this->Search(key);  // Use Search from RedBlackTree
        if (node == nullptr) {
            node = this->Insert(key, Type{});  // Insert if key not found
        }
        return node->value;
    }

    // Inserts a new key-value pair or updates value if key already exists
    void insert(const Key& key, const Type& value) {
        RBTNode<Key, Type>* node = this->Search(key);  // Check if key exists
        if (node == nullptr) {
            this->Insert(key, value);  // Insert new node if key doesn't exist
        } else {
            node->value = value;  // Update existing node's value
        }
    }

    // Removes node at specified iterator position
    void remove(iterator position) {
        if (position != nullptr) {
            this->RemoveNode(position);  // Use RemoveNode from RedBlackTree
        }
    }

    // Removes node with specified key and returns number of nodes removed (0 or 1)
    std::size_t remove(const Key& key) {
        return this->Remove(key);  // Use Remove from RedBlackTree
    }

    // Clears the entire tree by deleting nodes recursively
    void clear() {
        this->DeleteTree(this->root);  // Use DeleteTree from RedBlackTree
        this->root = nullptr;
    }

    // Checks if tree is empty
    bool empty() const {
        return this->root == nullptr;
    }

    // Returns the number of nodes in the tree
    std::size_t size() const {
        if (this->root == nullptr) {
            return 0;
        } else {
            return this->root->Count();  // Use Count method from RBTNode
        }
    }

    // Counts the occurrences of the specified key (0 or 1)
    std::size_t count(const Key& key) {
        return this->Search(key) != nullptr ? 1 : 0;
    }

    // Searches for a node with the specified key
    iterator find(const Key& key) {
        return this->Search(key);
    }

    // Checks if a specified key exists in the tree
    bool contains(const Key& key) {
        return this->Search(key) != nullptr;
    }

    // Converts the tree to a vector of key-value pairs using in-order traversal
    std::vector<std::pair<Key, Type>> toVector() {
        std::vector<std::pair<Key, Type>> vec;
        toVectorRecursive(this->root, vec);
        return vec;
    }

    // Displays the tree in a formatted string format
    void displayTree() {
        std::cout << RBTPrint<Key,Type>::TreeToString(this->root) << std::endl;
    }

    // Displays the tree nodes in an in-order traversal format
    void display() {
        displayRecursive(this->root);
    }

    // Helper function for toVector to recursively traverse the tree and add elements to vector
    void toVectorRecursive(RBTNode<Key, Type>* node, std::vector<std::pair<Key, Type>>& vec) {
        if (node == nullptr) {
            return;
        }
        toVectorRecursive(node->left, vec);
        vec.push_back({node->key, node->value});
        toVectorRecursive(node->right, vec);
    }

    // Helper function for display to recursively print each node's key and value
    void displayRecursive(RBTNode<Key, Type>* node) {
        if (node == nullptr) {
            return;
        }
        displayRecursive(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        displayRecursive(node->right);
    }
};

#endif
