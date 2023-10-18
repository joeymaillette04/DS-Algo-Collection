#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) {
    next = nullptr;
    prev = nullptr;
    value = data;
}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


DoublyLinkedList::~DoublyLinkedList() {
    while (head_ != nullptr) {
        Node *temp = head_;
        head_ = head_->next;
        delete temp;
        temp = nullptr;
      }
      tail_ = nullptr;
      size_ = 0;

}



unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    return (head_ == nullptr);
}


bool DoublyLinkedList::full() const {
    return (size_ == CAPACITY);
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    if (index > size_)
    {
        return(tail_->value);
    }

    return (getNode(index)->value);
}


unsigned int DoublyLinkedList::search(DataType value) const {
    Node* current = head_;
    for (unsigned int i = 0; i < size_; i++)
    {
        if(current->value == value) {
            return(i);
        }

        current = current->next;
    }
    return(size_);
    
}


void DoublyLinkedList::print() const {
    Node* current = head_;
    for (unsigned int i = 0; i < size_; i++)
    {
        std:: cout << current->value << std:: endl;
        current = current->next;
    }
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    Node* current = head_;

    for(unsigned int i = 0; i<index; i++) {
        current = current->next;
    }

    return(current);
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    if (index > size_ || full())
    {
        return false;
    }
    
    if (empty())
    {
        Node* newNode = new Node(value);
        head_ = newNode;
        tail_ = head_;
        size_++;
        return true;
    }

    if (index == 0)
    {
        insert_front(value);
        return true;
    }

    if (index == size_)
    {
        insert_back(value);
        return true;
    }

    Node* temp = new Node(value);
    Node* current;

    current = getNode(index-1);

    temp->next = current->next;
    current->next = temp;
    temp->prev = current;
    temp->next->prev = temp;
    size_++;

    return true;
}


bool DoublyLinkedList::insert_front(DataType value) {
    if (full())
    {
        return false;
    }
    
    if (empty())
    {
        Node* newNode = new Node(value);
        head_ = newNode;
        tail_ = head_;
        size_++;
        return true;
    }
    
    Node* previous = head_;
    Node* newHead = new Node(value);
   
    head_ = newHead;
    head_->next = previous;
    previous->prev = head_;

    size_++;
    return true;
}


bool DoublyLinkedList::insert_back(DataType value) {
    if (full())
    {
        return false;
    }
    
    if (empty())
    {
        Node* newNode = new Node(value);
        head_ = newNode;
        tail_ = head_;
        size_++;
        return true;
    }
    
    Node* previous = tail_;
    Node* newTail = new Node(value);
   
    tail_ = newTail;
    tail_->prev = previous;
    previous->next = tail_;

    size_++;
    return true; 
}


bool DoublyLinkedList::remove(unsigned int index) {
    if(empty() || index >= size_)
    {
        return false;
    }

    if (index == 0)
    {
        remove_front();
        return true;
    }

    if (index == size_-1)
    {
        remove_back();
        return true;
    }

    Node* previous = getNode(index-1);
    Node* deleting = previous->next;
    previous->next->next->prev = previous;
    previous->next = previous->next->next;

    delete deleting;
    deleting = nullptr;
    size_--;

    return true;
}


bool DoublyLinkedList::remove_front() {
    
    if(empty())
    {
        return false;
    }
    
    if (head_->next == nullptr) {
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }

    Node* temp = head_;
    head_ = head_->next;
    head_->prev = nullptr;

    delete temp;
    temp = nullptr;
    size_--;

    return true;
}


bool DoublyLinkedList::remove_back() {
    if(empty())
    {
        return false;
    }

    if (head_->next == nullptr) {
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }

    Node* temp = tail_;
    tail_ = tail_->prev;
    tail_->next = nullptr;

    delete temp;
    temp = nullptr;
    size_--;

    return true;
}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    if (index >= size_ || empty())
    {
        return false;
    }

    Node* temp = getNode(index);
    temp->value = value;
    return true;
}


// Created for testing purposes
void DoublyLinkedList::fillList(unsigned long int elements){
    for(unsigned long int i = 0; i<elements; i++)
    {
        insert_front(i);
    }
}

