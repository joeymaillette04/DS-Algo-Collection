#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
    head_ = 0;
    tail_ = 0;
    capacity_ = 16;
    size_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::CircularQueue(unsigned int capacity) {
    head_ = 0;
    tail_ = 0;
    capacity_ = capacity;
    size_ = 0;
    items_ = new QueueItem[capacity_];
}

CircularQueue::~CircularQueue() {
    delete []items_;
    items_ = nullptr;
}

unsigned int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::empty() const {
    return size_==0;
}

bool CircularQueue::full() const {
    return size_==capacity_;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if(empty()) {
        return EMPTY_QUEUE;
    }
    return items_[head_];
}

bool CircularQueue::enqueue(QueueItem value) {
    if (full()) {
        return false;
    }
    items_[tail_] = value;
    tail_++;

    if (tail_ == capacity_) {
        tail_ = 0;
    }

    size_++;
    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if (empty()) {
        return EMPTY_QUEUE;
    }

    QueueItem temp = items_[head_];
    items_[head_] = EMPTY_QUEUE;

    head_++;
    if (head_==capacity_) {
        head_ = 0;
    }
    size_--;
    return temp;
}

void CircularQueue::print() const {
    for(unsigned int i = 0; i<size_; i++) {
        std:: cout << items_[i] << ", ";
    }
}
