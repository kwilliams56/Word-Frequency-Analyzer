/*
 Name:Kravion Williams
 Email:Kwilliams56@crimson.ua.edu
 Course Section: Fall 2025 CS 201
 Homework #: 2
*/

#ifndef ST_HPP
#define ST_HPP

#include <vector>
#include <utility>
#include <iostream>
#include "RBT.hpp"
#include "RBTPrint.hpp"  // needed for TreeToString()

template <typename Key, typename Type>
class ST {
private:
    RedBlackTree<Key, Type> tree;

    // Helper: in-order traversal to vector
    void fillVector(std::vector<std::pair<Key, Type>>& vec, RBTNode<Key, Type>* node) {
        if (node == nullptr) return;
        fillVector(vec, node->left);
        vec.push_back({node->key, node->value});
        fillVector(vec, node->right);
    }

public:
    // ------------------------------------------------------------
    // Constructors / Destructor
    // ------------------------------------------------------------
    ST() = default;
    ~ST() { clear(); }

    // ------------------------------------------------------------
    // operator[] — insert if missing, return reference to value
    // ------------------------------------------------------------
    Type& operator[](const Key& key) {
        RBTNode<Key, Type>* node = tree.Search(key);
        if (node == nullptr) {
            tree.Insert(key, Type());
            node = tree.Search(key);
        }
        return node->value;
    }

    // ------------------------------------------------------------
    // insert(key,value)
    // ------------------------------------------------------------
    void insert(const Key& key, const Type& value) {
        RBTNode<Key, Type>* node = tree.Search(key);
        if (node != nullptr)
            node->value = value;  // replace existing
        else
            tree.Insert(key, value);
    }

    // ------------------------------------------------------------
    // remove(key)
    // ------------------------------------------------------------
    void remove(const Key& key) {
        tree.Remove(key);
    }

    // ------------------------------------------------------------
    // clear()
    // ------------------------------------------------------------
    void clear() {
        // Use whichever clear function exists
        if constexpr (requires { tree.Clear(); }) {
            tree.Clear();
        } else if constexpr (requires { tree.ClearTree(); }) {
            tree.ClearTree();
        } else {
            // fallback: repeatedly remove nodes
            while (tree.GetLength() > 0) {
                RBTNode<Key, Type>* root = tree.GetRoot();
                tree.Remove(root->key);
            }
        }
    }

    // ------------------------------------------------------------
    // empty()
    // ------------------------------------------------------------
    bool empty() {
        return tree.GetLength() == 0;
    }

    // ------------------------------------------------------------
    // size()
    // ------------------------------------------------------------
    size_t size() {
        return static_cast<size_t>(tree.GetLength());
    }

    // ------------------------------------------------------------
    // count(key)
    // ------------------------------------------------------------
    size_t count(const Key& key) {
        return tree.Search(key) ? 1 : 0;
    }

    // ------------------------------------------------------------
    // find(key)
    // ------------------------------------------------------------
    RBTNode<Key, Type>* find(const Key& key) {
        return tree.Search(key);
    }

    // ------------------------------------------------------------
    // contains(key)
    // ------------------------------------------------------------
    bool contains(const Key& key) {
        return tree.Search(key) != nullptr;
    }

    // ------------------------------------------------------------
    // toVector()
    // ------------------------------------------------------------
    std::vector<std::pair<Key, Type>> toVector() {
        std::vector<std::pair<Key, Type>> vec;
        fillVector(vec, tree.GetRoot());
        return vec;
    }

    // ------------------------------------------------------------
    // displayTree()
    // ------------------------------------------------------------
    void displayTree() {
        std::cout << ::RBTPrint<Key, Type>::TreeToString(tree.GetRoot()) << std::endl;
    }

    // ------------------------------------------------------------
    // display()
    // ------------------------------------------------------------
    void display() {
        std::vector<std::pair<Key, Type>> vec = toVector();
        for (auto& p : vec)
            std::cout << p.first << ": " << p.second << std::endl;
    }
};

#endif