#include "dynamic-stack.h"
#include <iostream>

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
    init_capacity_ = 16;
    capacity_ = init_capacity_;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity){
    capacity_ = capacity;
    init_capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack() {
    delete []items_;
    items_ = nullptr;
}

unsigned int DynamicStack::size() const {
    return(size_);
}

bool DynamicStack::empty() const {
    return(size_==0);
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (empty())
    {
        return(EMPTY_STACK);
    }
    else
    {
        return(items_[size_-1]);
    }
}

void DynamicStack::push(StackItem value) {
    if (size_==capacity_)
    {
        capacity_ *= 2;
        StackItem *tempArray;
        tempArray = new StackItem[capacity_];
        for (unsigned int i = 0; i<size_; i++)
        {
            tempArray[i] = items_[i];
        }
        int *last = items_;

        items_ = tempArray;

        tempArray = nullptr;
        delete []last;
        last = nullptr;
    }

    items_[size_] = value;
    size_++;
    return;
}

DynamicStack::StackItem DynamicStack::pop() {
    if (empty())
    {
        return(EMPTY_STACK);
    }
    StackItem temp;
    temp = items_[size_-1];

    items_[size_-1] = EMPTY_STACK;
    size_--;

    if (size_ < capacity_/4 && capacity_/2 >= init_capacity_)
    {
        capacity_ /= 2;
        StackItem *tempArray;
        tempArray = new StackItem[capacity_];
        for (unsigned int i = 0; i<size_; i++)
        {
            tempArray[i] = items_[i];
        }
        int *last = items_;

        items_ = tempArray;

        tempArray = nullptr;
        delete []last;
        last = nullptr;
    }
    return(temp);
}

void DynamicStack::print() const {
    for(int i = size_-1; i > -1; i--)
    {
        std:: cout<< items_[i] << std::endl;
    }
}
