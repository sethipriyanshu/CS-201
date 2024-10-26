/*
  Implementation: Symbol Table using Red-Black Tree
  Created by: Priyanshu Sethi
  Contact: psethi@crimson.ua.edu
  Course: CS 201 - Fall 2024
  Project: Assignment 2
*/

#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <iostream>
#include <utility>
#include <vector>

#include "RBT.hpp"
#include "RBTPrint.hpp"

template <class KeyType, class ValueType>
class SymbolTable : public RedBlackTree<KeyType, ValueType> {
private:
    std::size_t elementCount;

    // Recursive helper to convert tree to vector representation
    void traverseAndCollect(RBTNode<KeyType, ValueType>* currentNode, 
                           std::vector<std::pair<KeyType, ValueType> >& elements) const {
        if (currentNode != nullptr) {
            traverseAndCollect(currentNode->left, elements);
            elements.push_back(std::make_pair(currentNode->key, currentNode->value));
            traverseAndCollect(currentNode->right, elements);
        }
    }

    // Helper method for in-order printing
    void printInOrder(RBTNode<KeyType, ValueType>* currentNode) const {
        if (currentNode != nullptr) {
            printInOrder(currentNode->left);
            std::cout << "(" << currentNode->key << ", " << currentNode->value << ") ";
            printInOrder(currentNode->right);
        }
    }

public:
    // Define iterator type without using alias
    typedef RBTNode<KeyType, ValueType>* iterator;

    // Initialize empty symbol table
    SymbolTable() : elementCount(0) {}

    // Clean up allocated memory
    ~SymbolTable() {
        clearAll();
    }

    // Access or create element with given key
    ValueType& operator[](const KeyType& key) {
        iterator found = lookup(key);
        if (found == nullptr) {
            found = this->Insert(key, ValueType());
            if (found != nullptr) {
                elementCount++;
            }
        }
        return found->value;
    }

    // Add new key-value pair or update existing
    void insert(const KeyType& key, const ValueType& value) {
        iterator found = lookup(key);
        if (found != nullptr) {
            found->value = value;
        } else {
            iterator newNode = this->Insert(key, value);
            if (newNode != nullptr) {
                elementCount++;
            }
        }
    }

    // Delete element at specified position
    void erase(iterator pos) {
        if (pos != nullptr) {
            this->RemoveNode(pos);
            elementCount--;
        }
    }

    // Delete element with specified key
    std::size_t erase(const KeyType& key) {
        iterator found = lookup(key);
        if (found != nullptr) {
            this->Remove(key);
            elementCount--;
            return 1;
        }
        return 0;
    }

    // Remove all elements
    void clearAll() {
        if (this->root != nullptr) {
            this->DeleteTree(this->root);
            this->root = nullptr;
            elementCount = 0;
        }
    }

    // Check if table is empty
    bool empty() const {
        return elementCount == 0;
    }

    // Get number of elements
    std::size_t size() const {
        return elementCount;
    }

    // Check if key exists in table
    std::size_t count(const KeyType& key) const {
        return (lookup(key) != nullptr) ? 1 : 0;
    }

    // Find node with given key
    iterator lookup(const KeyType& key) {
        return this->Search(key);
    }

    // Check key existence
    bool exists(const KeyType& key) const {
        return lookup(key) != nullptr;
    }

    // Get sorted vector of all elements
    std::vector<std::pair<KeyType, ValueType> > toVector() const {
        std::vector<std::pair<KeyType, ValueType> > elements;
        traverseAndCollect(this->root, elements);
        return elements;
    }

    // Print tree structure
    void printTree() const {
        std::cout << RBTPrint<KeyType, ValueType>::TreeToString(this->root) << std::endl;
    }

    // Print elements in sorted order
    void print() const {
        printInOrder(this->root);
        std::cout << std::endl;
    }
};

#endif