#include "binary-search-tree.h"
#include <queue>
#include <iostream>
#include <algorithm>


BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == nullptr) {return 0;}

    else if (n->left == nullptr && n->right == nullptr) {
        return 0;
    }

    else {
        return (1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right)));
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    if (root_ == nullptr) {return;}

    std::queue <Node*> Q;
    Q.push(root_);

    while(!Q.empty()) {
        Node* P = Q.front();
        if (P->left != nullptr) {
            Q.push(P->left);
        }
        if (P->right != nullptr) {
            Q.push(P->right);
        }
        Q.pop();
        delete P;
    }
    
}

unsigned int BinarySearchTree::size() const {
    return(size_);
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    if(root_ == nullptr) {return(-999);}
    
    Node* current = root_;
    while(current->right != nullptr) {
        current=current->right;
    }
    return(current->val);
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    if(root_ == nullptr) {return(-999);}

    Node* current = root_;
    while(current->left != nullptr) {
        current=current->left;
    }
    return(current->val);
}

unsigned int BinarySearchTree::depth() const {
    return (getNodeDepth(root_));
}

void BinarySearchTree::print() const {
    if(root_ == nullptr){return;}
    
    std:: queue <Node*> Q;
    Q.push(root_);

    while(!Q.empty()) {
        Node *cur = Q.front();
        std:: cout << cur->val << ", ";
        Q.pop();
        if (cur->left != nullptr) {Q.push(cur->left);}
        if (cur->right != nullptr) {Q.push(cur->right);}

    }
}


bool BinarySearchTree::exists(DataType val) const {
    Node* current = root_;

    while (current!=nullptr) {

        if(current->val == val) {
            return true;
        }
        else if (current->val < val) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return(root_);
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return(&root_);
}

bool BinarySearchTree::insert(DataType val) {
    if (exists(val)) {
        return false;
    }

    Node* inserting = new Node(val);

    if (root_ == nullptr) {
        root_ = inserting;
        size_++;
        return true;
    }

    Node* current = root_;

    while(current!=nullptr) {

        if (current->val < val) {
            if (current->right == nullptr) {
                current->right = inserting;
                size_++;
                return true;
            }
            current = current->right;
        }

        else {
            if (current->left == nullptr) {
                current->left = inserting;
                size_++;
                return true;
            }
            current = current-> left;
        }
    }
    return false;
    
}

bool BinarySearchTree::remove(DataType val) {
    if(!exists(val)) {return false;}
    
    Node* curr = root_;
    Node* currParent = nullptr;
    bool isRightChild = false;

    // find the node and its parent
    while(curr!=nullptr) {
        if(curr->val == val) {
            break;
        }
        else if (val < curr->val) {
            currParent = curr;
            curr = curr->left;
            isRightChild = false;
        }
        else {
            currParent = curr;
            curr = curr->right;
            isRightChild = true;
        }
    }

    // if its a leaf node
    if (curr->left==nullptr && curr->right==nullptr) {

        // special case for 1 node tree
        if(curr == root_) {
            delete root_;
            root_ = nullptr;
            size_--;
            return true;
        }
        // standard case
        delete curr;
        curr = nullptr;
        if(isRightChild) {currParent->right = nullptr;}
        else {currParent->left = nullptr;}
        size_--;
        return true;
    }

    // one child node
    if(curr->left==nullptr && curr->right!=nullptr) {
        if(isRightChild) {currParent->right = curr->right;}
        else if (curr->val == root_->val) {root_ = curr->right;}
        else {currParent->left = curr->right;}
        
        delete curr;
        curr = nullptr;
        size_--;
        return true;
    }
    // one child node
    else if(curr->right==nullptr && curr->left!=nullptr) {
        if(isRightChild) {currParent->right = curr->left;}
        else if (curr->val == root_->val) {root_ = curr->left;}
        else {currParent->left = curr->left;}
        delete curr;
        curr = nullptr;
        size_--;
        return true;
    }
    //two child nodes
    if(curr->left!=nullptr && curr->right!=nullptr) {
        Node* predecessor = curr->left;
        isRightChild = false;
        Node* preParent = curr;

        while(predecessor->right != nullptr) {
            preParent = predecessor;
            predecessor = predecessor->right;
            isRightChild = true;
        }

        curr->val = predecessor->val;
        if(predecessor->left == nullptr && isRightChild) {
            preParent->right = nullptr;
        }
        else if(predecessor->left == nullptr) {
            preParent->left = nullptr;
        }
        else if (predecessor->left != nullptr && isRightChild) {
            preParent->right = predecessor->left;
        }
        else {
            preParent->left = predecessor->left;
        }

        delete predecessor;
        predecessor = nullptr;
        size_--;
        return true;
    }
}