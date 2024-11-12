/*
  Author: Priyanshu Sethi
  Email: psethi@crimson.ua.edu
  Section: Fall 2024 CS 201
  Assignment: 2
*/

#ifndef ST_HPP
#define ST_HPP

#include <utility>
#include <vector>
#include <iostream>
#include "RBT.hpp"
#include "RBTPrint.hpp"

template <class Key, class Type>
class ST : public RedBlackTree<Key, Type> {
public:
    using iterator = RBTNode<Key, Type>*;

    // Constructor
    ST() : nodeCount(0) {}

    // Destructor
    ~ST() {
        clear();
    }

    // Access or insert element
    Type& operator[](const Key& key) {
    iterator node = find(key);
    if (node == nullptr) {
        node = this->Insert(key, Type());  // Get node directly from Insert
        if (node != nullptr) {
            nodeCount++;
        }
    }
    return node->value;
}

    // Insert a (key, value) pair
    void insert(const Key& key, const Type& value) {
    iterator node = find(key);
    if (node != nullptr) {
        node->value = value;
    } else {
        node = this->Insert(key, value);  // Get node directly
        if (node != nullptr) {
            nodeCount++;
        }
    }
}

    // Remove element at given position
    void remove(iterator position) {
        if (position != nullptr) {
            this->RemoveNode(position);  // Use RemoveNode from RedBlackTree
            nodeCount--;
        }
    }

    // Remove element with given key
    std::size_t remove(const Key& key) {
        iterator node = find(key);
        if (node != nullptr) {
            this->Remove(key);  // Use Remove from RedBlackTree
            nodeCount--;
            return 1;
        }
        return 0;
    }

    // Clear all elements
    void clear() {
    if (this->root != nullptr) {
        this->DeleteTree(this->root);
        this->root = nullptr;  // Nullify root after deletion
        nodeCount = 0;
    }
}


    // Check if ST is empty
    bool empty() const {
        return nodeCount == 0;
    }

    // Get size of ST
    std::size_t size() const {
        return nodeCount;
    }

    // Count occurrences of key
    std::size_t count(const Key& key) const {
        return (find(key) != nullptr) ? 1 : 0;
    }

    // Find element with given key
    iterator find(const Key& key) {
        return this->Search(key);  // Use Search from RedBlackTree
    }

    // Check if key exists
    bool contains(const Key& key) const {
        return find(key) != nullptr;
    }

    // Convert to vector of pairs
    std::vector<std::pair<Key, Type>> toVector() const {
        std::vector<std::pair<Key, Type>> result;
        inorderToVector(this->root, result);  // Helper function defined below
        return result;
    }

    // Display tree structure
    void displayTree() const {
        std::cout << RBTPrint<Key,Type>::TreeToString(this->root) << std::endl;  // Use RBTPrint for tree visualization
    }

    // Display in sorted order
    void display() const {
        inorderDisplay(this->root);  // Helper function defined below
        std::cout << std::endl;
    }

private:
    std::size_t nodeCount;

    // Helper function for toVector
    void inorderToVector(iterator node, std::vector<std::pair<Key, Type>>& result) const {
        if (node != nullptr) {
            inorderToVector(node->left, result);
            result.push_back(std::make_pair(node->key, node->value));
            inorderToVector(node->right, result);
        }
    }

    // Helper function for display
    void inorderDisplay(iterator node) const {
        if (node != nullptr) {
            inorderDisplay(node->left);
            std::cout << "(" << node->key << ", " << node->value << ") ";
            inorderDisplay(node->right);
        }
    }
};

#endif