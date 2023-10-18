#include "avl-tree.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>


bool AVLTree::insert(DataType val) {
    BinarySearchTree::insert(val);
    balance(val);
    return true;
}

bool AVLTree::remove(DataType val) {
    BinarySearchTree::remove(val);
    balance(val); 
    return true;
}

bool AVLTree::leftRot(Node *alpha, Node *parent) {
    Node* A = nullptr;
    Node** root = BinarySearchTree::getRootNodeAddress();

    //find A
    if (depthOfNode(alpha->left) > depthOfNode(alpha->right)) {
        A = alpha->left;
    }

    else {
        A = alpha->right;
    }

    if(parent == nullptr){
        alpha->right = A->left;
        A->left = alpha;
        *root = A;
        return true;
    }

    alpha->right = A->left;
    A->left = alpha;
    if(parent->left == alpha) {
        parent->left = A;
    }
    else {
        parent->right = A;
    }
    return true;
}

bool AVLTree::rightRot(Node *alpha, Node *parent) {
    Node* A = nullptr;
    Node** root = BinarySearchTree::getRootNodeAddress();


    //find A
    if (depthOfNode(alpha->left) > depthOfNode(alpha->right)) {
        A = alpha->left;
    }

    else {
        A = alpha->right;
    }


    if(parent == nullptr){
        alpha->left = A->right;
        A->right = alpha;
        *root = A;
        return true;
    }

    //apply rotation
    alpha->left = A->right;
    A->right = alpha;
    if(parent->left == alpha) {
        parent->left = A;
    }
    else {
        parent->right = A;
    }
    
    return true;
}

bool AVLTree::balance(DataType val) {

    Node* parent = nullptr;
    Node* A = nullptr;
    Node* AChild = nullptr;
    Node* alpha = nullptr;

    Node* curr = BinarySearchTree::getRootNode();
    Node* prev = nullptr;
    

    // iterate through entire depth of tree
    while (curr!=nullptr){

        // finds closest unbalanced node to value
        if (abs(depthOfNode(curr->left) - depthOfNode(curr->right))==2) {
            alpha = curr;
            parent = prev;
            
        }

        prev = curr;

        if (val>curr->val){
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }

    //no unbalanced node = no balance needed
    if (alpha == nullptr)
        return true;


    if (depthOfNode(alpha->left) > depthOfNode(alpha->right)) {
        A = alpha->left;
    }

    else {
        A = alpha->right;
    }


    //screws up without this in the case of removing a node
    if (depthOfNode(A->left) > depthOfNode(A->right))
        AChild = A->left;

    else
        AChild = A->right;


    //right rotation
    if (AChild->val < alpha->val && AChild->val < A->val){
        rightRot(alpha, parent);
    }

    //left rotation
    else if (AChild->val > alpha->val && AChild->val > A->val){
        leftRot(alpha, parent);
    }

    //left right rotation
    else if (AChild->val < alpha->val && AChild->val > A->val){
        leftRot(A, alpha);
        rightRot(alpha, parent);
    }

    //right left rotation
    else {
        rightRot(A, alpha);
        leftRot(alpha, parent);
    }

    return true;

}

int AVLTree::depthOfNode(Node* n) {
    if (n == nullptr) {return 0;}

    else if (n->left == nullptr && n->right == nullptr) {
        return 1;
    }

    else {
        return (1 + std::max(depthOfNode(n->left), depthOfNode(n->right)));
    }
}