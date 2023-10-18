#ifndef LAB3_AVL_TREE_H
#define LAB3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree : public BinarySearchTree {

public:
    // Overriden insert and remove functions
    // Do not modify these definitions
    
    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);
    bool leftRot(Node* alpha, Node* parent);
    bool rightRot(Node* alpha, Node* parent);
    bool balance(DataType val);
    int depthOfNode(Node* n);


    // Define additional functions and attributes below if you need
};

#endif  // LAB3_AVL_TREE_H
